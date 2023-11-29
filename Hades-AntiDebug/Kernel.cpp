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
