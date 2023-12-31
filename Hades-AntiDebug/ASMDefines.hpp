#pragma once

#include "KernelTypes.hpp"


namespace HadesInternals
{
    extern "C" NTSTATUS Internal_NtQueryVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, Hades::MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation, SIZE_T MemoryInformationLength, PSIZE_T ReturnLength);
    extern "C" NTSTATUS Internal_NtQueryInformationProcess(HANDLE ProcessHandle, Hades::PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);
    extern "C" NTSTATUS Internal_NtTerminateProcess(HANDLE ProcessHandle, UINT ExitStatus);
    extern "C" NTSTATUS Internal_NtOpenProcess(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, CLIENT_ID* ClientId);
    extern "C" NTSTATUS Internal_NtClose(HANDLE Handle);
    extern "C" NTSTATUS Internal_NtReadVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesReaded);
    extern "C" NTSTATUS Internal_NtAllocateVirtualMemory(HANDLE ProcessHandle, PVOID * BaseAddress, ULONG_PTR ZeroBits, PSIZE_T RegionSize, ULONG AllocationType, ULONG Protect);
    extern "C" NTSTATUS Internal_NtFreeVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, PSIZE_T RegionSize, ULONG FreeType);
    extern "C" NTSTATUS Internal_NtGetContextThread(HANDLE ThreadHandle, PCONTEXT pContext);

}