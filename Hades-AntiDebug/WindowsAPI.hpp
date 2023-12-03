#pragma once

namespace Hades
{
	namespace WindowsAPI
	{
		SIZE_T VirtualQuery(
			LPCVOID lpAddress,
			PMEMORY_BASIC_INFORMATION lpBuffer,
			SIZE_T dwLength
		);

		DWORD GetProcessId(
			HANDLE Process
		);

		/*
		* Checking if debugger is present by reading remote process PEB
		*/
		BOOL CheckRemoteDebuggerPresent(
			HANDLE hProcess,
			PBOOL pbDebuggerPresent
		);

		/*
		* Checking if debugger is present by reading process PEB
		*/
		BOOL IsDebuggerPresent();

		HANDLE OpenProcess(
			DWORD dwDesiredAccess,
			BOOL bInheritHandle,
			DWORD dwProcessId
		);
		
		BOOL CloseHandle(
			HANDLE hObject
		);

		/*LPVOID VirtualAllocExNuma(
			HANDLE hProcess,
			LPVOID lpAddress,
			SIZE_T dwSize,
			DWORD flAllocationType,
			DWORD flProtect,
			DWORD nndPreferred
		);

		LPVOID VirtualAllocEx(
			HANDLE hProcess,
			LPVOID lpAddress,
			SIZE_T dwSize,
			DWORD flAllocationType,
			DWORD flProtect
		);*/
	}
}
