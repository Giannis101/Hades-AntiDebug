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


       /*
       * Opens a handle to a process object and sets the access rights to this object.
       * https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddk/nf-ntddk-ntopenprocess
       */
        NTSTATUS NtOpenProcess(
            PHANDLE ProcessHandle,
            ACCESS_MASK DesiredAccess,
            POBJECT_ATTRIBUTES ObjectAttributes,
            CLIENT_ID* ClientId
        );


       /*
       * Closes the specified handle.
       * https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntclose
       */
        NTSTATUS NtClose(
            HANDLE Handle
        );


       /*
       * Similar to ReadProcessMemory.
       * https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-readprocessmemory
       */
        NTSTATUS NtReadVirtualMemory(
            HANDLE ProcessHandle,
            PVOID BaseAddress,
            PVOID Buffer,
            ULONG NumberOfBytesToRead,
            PULONG NumberOfBytesReaded
        );
        

       /*
       * Reserves, commits, or both, a region of pages within the user-mode virtual address space of a specified process.
       * https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntallocatevirtualmemory
       */
        NTSTATUS NtAllocateVirtualMemory(
            HANDLE ProcessHandle,
            PVOID* BaseAddress,
            ULONG_PTR ZeroBits,
            PSIZE_T RegionSize,
            ULONG AllocationType,
            ULONG Protect
        );


        /*
       * Releases, decommits, or both releases and decommits, a region of pages within the virtual address space of a specified process.
       * https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntfreevirtualmemory
       */
        NTSTATUS NtFreeVirtualMemory(
            HANDLE ProcessHandle,
            PVOID* BaseAddress,
            PSIZE_T RegionSize,
            ULONG FreeType
        );

    }
}