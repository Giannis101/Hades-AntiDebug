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

BOOL Hades::WindowsAPI::IsDebuggerPresent()
{
    PPEB pPeb = (PPEB)__readgsqword(0x60);
    return pPeb->BeingDebugged;
}

HANDLE Hades::WindowsAPI::OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId)
{
    HANDLE handle = NULL;
    CLIENT_ID clientId{};
    OBJECT_ATTRIBUTES objAttributes{};

    InitializeObjectAttributes(&objAttributes, NULL, (bInheritHandle ? OBJ_INHERIT : NULL), NULL, NULL);
    clientId.UniqueProcess = (HANDLE)dwProcessId;

    if (Kernel::NtOpenProcess(&handle, (ACCESS_MASK)dwDesiredAccess, &objAttributes, &clientId) == STATUS_SUCCESS)
    {
        return handle;
    }

    return NULL;
}

BOOL Hades::WindowsAPI::CloseHandle(HANDLE hObject)
{
    if (Kernel::NtClose(hObject) == STATUS_SUCCESS)
    {
        return TRUE;
    }

    return FALSE;
}

HANDLE Hades::WindowsAPI::GetCurrentThread()
{
    return Kernel::NtCurrentThread();
}

HANDLE Hades::WindowsAPI::GetCurrentProcess()
{
    return Kernel::NtCurrentProcess();
}

BOOL Hades::WindowsAPI::GetThreadContext(HANDLE hThread, LPCONTEXT lpContext)
{
    if (Kernel::NtGetContextThread(hThread, lpContext) == STATUS_SUCCESS)
    {
        return TRUE;
    }

    return FALSE;
}

//LPVOID Hades::WindowsAPI::VirtualAllocExNuma(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect, DWORD nndPreferred)
//{
//    LPVOID baseAddress = lpAddress;
//    SIZE_T regionSize = dwSize;
//    if (Kernel::NtAllocateVirtualMemory(hProcess, &baseAddress, NULL, &regionSize, (ULONG)flAllocationType, (ULONG)flProtect) == STATUS_SUCCESS)
//    {
//        return baseAddress;
//    }
//
//    return NULL;
//}
//
//LPVOID Hades::WindowsAPI::VirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect)
//{
//    return VirtualAllocExNuma(hProcess, lpAddress, dwSize, flAllocationType, flProtect, 0xFFFFFFFF);
//}

