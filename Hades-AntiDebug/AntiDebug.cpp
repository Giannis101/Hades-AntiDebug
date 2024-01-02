#include "pch.hpp"
#include "Kernel.hpp"
#include "WindowsAPI.hpp"
#include "HadesAPI.hpp"
#include "AntiDebug.hpp"



bool Hades::AntiDebug::HasDetectedProcessDebugFlags()
{
    return HasDetectedProcessDebugFlags(Kernel::NtCurrentProcess());
}

bool Hades::AntiDebug::HasDetectedProcessDebugObject()
{
    return HasDetectedProcessDebugObject(Kernel::NtCurrentProcess());
}

bool Hades::AntiDebug::HasDetectedProcessDebugFlags(HANDLE process)
{
    ULONG debugFlags = 0;
    if (Kernel::NtQueryInformationProcess(Kernel::NtCurrentProcess(), PROCESSINFOCLASS::ProcessDebugFlags, &debugFlags, sizeof(ULONG), NULL) == STATUS_SUCCESS)
    {
        if (debugFlags == 0) return true;
    }

    return false;
}

bool Hades::AntiDebug::HasDetectedProcessDebugObject(HANDLE process)
{
    HANDLE debugHandle = NULL;
    if (Kernel::NtQueryInformationProcess(Kernel::NtCurrentProcess(), PROCESSINFOCLASS::ProcessDebugObjectHandle, &debugHandle, sizeof(HANDLE), NULL) == STATUS_SUCCESS)
    {
        if (debugHandle != NULL) return true;
    }

    return false;
}

bool Hades::AntiDebug::HasDetectedHardwareBreakpoints()
{
    bool result = false;

    LPVOID baseAddress = NULL;
    SIZE_T regionSize = sizeof(CONTEXT);
    if (Kernel::NtAllocateVirtualMemory(Kernel::NtCurrentProcess(), &baseAddress, NULL, &regionSize, MEM_COMMIT, PAGE_READWRITE) == STATUS_SUCCESS)
    {
        if (regionSize >= sizeof(CONTEXT))
        {
            PCONTEXT context = (PCONTEXT)baseAddress;
            context->ContextFlags = CONTEXT_DEBUG_REGISTERS;

            if (WindowsAPI::GetThreadContext(WindowsAPI::GetCurrentThread(), context))
            {
                //not sure if should also check Dr6 and Dr7
                result = (context->Dr0 != 0ull || context->Dr1 != 0ull || context->Dr2 != 0ull || context->Dr3 != 0ull);
            }
        }

        Kernel::NtFreeVirtualMemory(Kernel::NtCurrentProcess(), &baseAddress, 0, MEM_RELEASE);
    }

    return result;
}

wchar_t* Hades::AntiDebug::GetParentProcessFileName(bool includeParentPath)
{
    return GetParentProcessFileName(Kernel::NtCurrentProcess(), includeParentPath);
}

wchar_t* Hades::AntiDebug::GetParentProcessFileName(HANDLE process, bool includeParentPath)
{
    if (DWORD pid = HadesAPI::GetParentProcessProcessId(process))
    {
        if (HANDLE parentProcess = WindowsAPI::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid))
        {
            wchar_t* result = HadesAPI::GetProcessFileName(parentProcess, includeParentPath);
            WindowsAPI::CloseHandle(parentProcess);
            return result;
        }
    }

    return nullptr;
}

bool Hades::AntiDebug::TerminateParentProcess(int exitCode)
{
    return TerminateParentProcess(Kernel::NtCurrentProcess(), exitCode);
}

bool Hades::AntiDebug::TerminateParentProcess(HANDLE process, int exitCode)
{
    if (DWORD pid = HadesAPI::GetParentProcessProcessId(process))
    {
        if (HANDLE parentProcess = WindowsAPI::OpenProcess(PROCESS_TERMINATE, FALSE, pid))
        {
            bool result = (Kernel::NtTerminateProcess(parentProcess, (UINT)exitCode) == STATUS_SUCCESS);
            WindowsAPI::CloseHandle(parentProcess);
            return result;
        }
    }

    return false;
}

void Hades::AntiDebug::TerminateCurrentProcess(int exitCode)
{
    Kernel::NtTerminateProcess(Kernel::NtCurrentProcess(), (UINT)exitCode);
}
