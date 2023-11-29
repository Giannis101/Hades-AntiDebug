#pragma once

#include "KernelTypes.hpp"


namespace Hades
{
    namespace Kernel
    {
        /*
        * Returns a handle to the current process.
        * The returned value is not a true handle, but it is a special value that always represents the current process.
        * https://learn.microsoft.com/en-us/windows-hardware/drivers/kernel/zwcurrentprocess
        */
        HANDLE NtCurrentProcess();


        /*
        * Determines the state, protection, and type of a region of pages within the virtual address space of the specified process.
        * https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntqueryvirtualmemory
        */
        NTSTATUS NtQueryVirtualMemory(
            HANDLE ProcessHandle,
            PVOID BaseAddress,
            MEMORY_INFORMATION_CLASS MemoryInformationClass,
            PVOID MemoryInformation,
            SIZE_T MemoryInformationLength,
            PSIZE_T ReturnLength
        );


        /*
        * Retrieves information about the specified process.
        * https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntqueryinformationprocess
        */
        NTSTATUS NtQueryInformationProcess(
            HANDLE ProcessHandle,
            PROCESSINFOCLASS ProcessInformationClass,
            PVOID ProcessInformation,
            ULONG ProcessInformationLength,
            PULONG ReturnLength
        );


       /*
       * Terminates a process and all of its threads.
       * https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddk/nf-ntddk-zwterminateprocess
       */
        NTSTATUS NtTerminateProcess(
            HANDLE ProcessHandle,
            UINT ExitStatus
        );
    }
}