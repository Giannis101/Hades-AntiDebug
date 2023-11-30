#include "pch.hpp"
#include "ASMDefines.hpp"
#include "Kernel.hpp"



HANDLE Hades::Kernel::NtCurrentProcess()
{
	return (HANDLE)0xFFFFFFFFFFFFFFFF;
}

NTSTATUS Hades::Kernel::NtQueryVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, MEMORY_INFORMATION_CLASS MemoryInformationClass, PVOID MemoryInformation, SIZE_T MemoryInformationLength, PSIZE_T ReturnLength)
{
	return HadesInternals::Internal_NtQueryVirtualMemory(ProcessHandle, BaseAddress, MemoryInformationClass, MemoryInformation, MemoryInformationLength, ReturnLength);
}

NTSTATUS Hades::Kernel::NtQueryInformationProcess(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength)
{
	return HadesInternals::Internal_NtQueryInformationProcess(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
}

NTSTATUS Hades::Kernel::NtTerminateProcess(HANDLE ProcessHandle, UINT ExitStatus)
{
	return HadesInternals::Internal_NtTerminateProcess(ProcessHandle, ExitStatus);
}

NTSTATUS Hades::Kernel::NtOpenProcess(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, CLIENT_ID* ClientId)
{
	return HadesInternals::Internal_NtOpenProcess(ProcessHandle, DesiredAccess, ObjectAttributes, ClientId);
}

NTSTATUS Hades::Kernel::NtClose(HANDLE Handle)
{
	return HadesInternals::Internal_NtClose(Handle);
}

NTSTATUS Hades::Kernel::NtReadVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesReaded)
{
	return HadesInternals::Internal_NtReadVirtualMemory(ProcessHandle, BaseAddress, Buffer, NumberOfBytesToRead, NumberOfBytesReaded);
}
