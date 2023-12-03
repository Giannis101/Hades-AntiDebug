#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <psapi.h>


#pragma comment (lib, "../x64/Release/Hades-AntiDebug.lib")    //include Hades anti-debugging library

#include "../Hades-AntiDebug/Kernel.hpp"      //include this only if you want access kernel functions (Hades::Kernel). Otherwise no need.
#include "../Hades-AntiDebug/WindowsAPI.hpp"    //include this only if you want use Windows API functions throu Hades (Hades::WindowsAPI). Otherwise no need.
#include "../Hades-AntiDebug/AntiDebug.hpp"     //include this if want to use Hades::AntiDebug functions



void PrintBool(const char* description, bool result)
{
	std::cout << description << " : " << (result ? "YES" : "NO") << std::endl;
}

bool Windows_HasDetectedProcessDebugFlags()
{
	if (HMODULE nttdll = GetModuleHandleA("ntdll.dll"))
	{
		using fpNtQueryInformationProcess = NTSTATUS(NTAPI*)(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);
		auto NtQueryInformationProcess = (fpNtQueryInformationProcess)GetProcAddress(nttdll, "NtQueryInformationProcess");

		ULONG processDebugFlags = NULL;
		if (NtQueryInformationProcess(GetCurrentProcess(), (PROCESSINFOCLASS)0x1F, &processDebugFlags, sizeof(ULONG), NULL) == STATUS_SUCCESS)
		{
			return processDebugFlags == NULL;
		}
	}
	
	return false;
}

bool Windows_HasDetectedProcessDebugObject()
{
	if (HMODULE nttdll = GetModuleHandleA("ntdll.dll"))
	{
		using fpNtQueryInformationProcess = NTSTATUS(NTAPI*)(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);
		auto NtQueryInformationProcess = (fpNtQueryInformationProcess)GetProcAddress(nttdll, "NtQueryInformationProcess");

		HANDLE processDebugObjectHandle = NULL;
		if (NtQueryInformationProcess(GetCurrentProcess(), (PROCESSINFOCLASS)0x1E, &processDebugObjectHandle, sizeof(HANDLE), NULL) == STATUS_SUCCESS)
		{
			return processDebugObjectHandle != NULL;
		}
	}

	return false;
}

//This function using normal windows API to get parent process name. Debugger-hide tools can spoof this to looks like its opened without any debugger.
wchar_t* Windows_GetParentProcessFileName()
{
	DWORD pid = GetCurrentProcessId();
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W pe = { 0 };
	pe.dwSize = sizeof(PROCESSENTRY32W);
	wchar_t* result = nullptr;

	if (h != INVALID_HANDLE_VALUE)
	{
		if (Process32FirstW(h, &pe))
		{
			do
			{
				if (pe.th32ProcessID == pid)
				{
					if (HANDLE parentProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe.th32ParentProcessID))
					{
						result = new wchar_t[MAX_PATH] {};
						GetModuleFileNameExW(parentProcess, NULL, result, MAX_PATH);
					}

					break;
				}
			} while (Process32NextW(h, &pe));
		}

		CloseHandle(h);
	}

	return result;
}




int main()
{
	while (true)
	{
		std::cout << "Checking if debugger is present in this process" << std::endl << std::endl;

		///////////////////////////////////////////////////////////////  HADES  ///////////////////////////////////////////////////////////////
		PrintBool("Hades - HasDetectedProcessDebugFlags", Hades::AntiDebug::HasDetectedProcessDebugFlags());
		PrintBool("Hades - HasDetectedProcessDebugObject", Hades::AntiDebug::HasDetectedProcessDebugObject());
		//PrintBool("Hades - HasDetectedHardwareBreakpoints", Hades::AntiDebug::HasDetectedHardwareBreakpoints());

		BOOL hadesRemoteDebug = FALSE;
		if (Hades::WindowsAPI::CheckRemoteDebuggerPresent(GetCurrentProcess(), &hadesRemoteDebug)) //call CheckRemoteDebuggerPresent with Hades. Not recommented, attackers can still spoof it
		{
			PrintBool("Hades (WindowsAPI) - HasDetectedProcessDebugObject", (bool)hadesRemoteDebug);
		}

		if (wchar_t* debugName = Hades::AntiDebug::GetParentProcessFileName())
		{
			std::wcout << "Hades - GetParentProcessFileName: " << debugName << std::endl;
			delete[] debugName;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		std::cout << std::endl << std::endl;

		////////////////////////////////////////////////////////////  WINDOWS  ////////////////////////////////////////////////////////////////
		PrintBool("Windows - HasDetectedProcessDebugFlags", Windows_HasDetectedProcessDebugFlags());
		PrintBool("Windows - HasDetectedProcessDebugObject", Windows_HasDetectedProcessDebugObject());

		BOOL normalRemoteDebug = FALSE;
		if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &normalRemoteDebug)) //call CheckRemoteDebuggerPresent normally
		{
			PrintBool("Windows - HasDetectedProcessDebugObject", (bool)normalRemoteDebug);
		}

		PrintBool("Windows - IsDebuggerPresent", IsDebuggerPresent());

		if (wchar_t* debugName = Windows_GetParentProcessFileName())
		{
			std::wcout << "Windows - parent process name: " << debugName << std::endl;
			delete[] debugName;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::cout << std::endl << std::endl;

		//a simple test to detect if a debugger-hide tool is currently used to hide the debugger
		bool windowsDetectedDebug = Windows_HasDetectedProcessDebugFlags() || Windows_HasDetectedProcessDebugObject();
		bool hadesDetectedDebug = Hades::AntiDebug::HasDetectedProcessDebugFlags() || Hades::AntiDebug::HasDetectedProcessDebugObject();

		if (hadesDetectedDebug && !windowsDetectedDebug)
		{
			std::cout << "Debugger-hide tool/s detected" << std::endl;
		}


		Sleep(1000);
		system("cls"); //clear console
	}
	return 0;
}
