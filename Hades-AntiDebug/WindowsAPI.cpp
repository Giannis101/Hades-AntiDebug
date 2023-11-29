#include "pch.hpp"
#include "Kernel.hpp"
#include "WindowsAPI.hpp"


SIZE_T Hades::WindowsAPI::VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength)
{
    SIZE_T written = 0;
    if (Kernel::NtQueryVirtualMemory(Kernel::NtCurrentProcess(), (LPVOID)lpAddress, MEMORY_INFORMATION_CLASS::MemoryBasicInformation, lpBuffer, dwLength, &written) == STATUS_SUCCESS)
    {
        return written;
    }

    return 0;
}

DWORD Hades::WindowsAPI::GetProcessId(HANDLE Process)
{
    PROCESS_BASIC_INFORMATION info{};
    if (Kernel::NtQueryInformationProcess(Process, PROCESSINFOCLASS::ProcessBasicInformation, &info, sizeof(PROCESS_BASIC_INFORMATION), nullptr) == STATUS_SUCCESS)
    {
        return (DWORD)info.UniqueProcessId;
    }

    return 0;
}

BOOL Hades::WindowsAPI::CheckRemoteDebuggerPresent(HANDLE hProcess, PBOOL pbDebuggerPresent)
{
    PROCESS_BASIC_INFORMATION info{};
    if (Kernel::NtQueryInformationProcess(hProcess, PROCESSINFOCLASS::ProcessBasicInformation, &info, sizeof(PROCESS_BASIC_INFORMATION), nullptr) == STATUS_SUCCESS)
    {
        if (info.PebBaseAddress && pbDebuggerPresent)
        {
            *pbDebuggerPresent = info.PebBaseAddress->BeingDebugged;
            return TRUE;
        }
    }

    return FALSE;
}