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

bool Windows_HasDetectedHardwareBreakpoints()
{
	bool result = false;

	if (PCONTEXT context = (PCONTEXT)VirtualAlloc(NULL, sizeof(CONTEXT), MEM_COMMIT, PAGE_READWRITE))
	{
		context->ContextFlags = CONTEXT_DEBUG_REGISTERS;

		if (GetThreadContext(GetCurrentThread(), context))
		{
			//not sure if should also check Dr6 and Dr7
			result = (context->Dr0 != 0ull || context->Dr1 != 0ull || context->Dr2 != 0ull || context->Dr3 != 0ull);
		}

		VirtualFree(context, 0, MEM_RELEASE);
	}

	return result;
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

//change console window background and text color
void SetGameOverColors()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// run all hades checks, print result messages, return true if detect debugger using Hades otherwise return false
bool RunHadesChecks()
{
	bool hades_hasDetectedProcessDebugFlags = Hades::AntiDebug::HasDetectedProcessDebugFlags();
	bool hades_hasDetectedProcessDebugObject = Hades::AntiDebug::HasDetectedProcessDebugObject();
	bool hades_hasDetectedHardwareBreakpoints = Hades::AntiDebug::HasDetectedHardwareBreakpoints();
	bool hades_checkRemoteDebuggerPresent = false;							//checking for remote debugger present not recommented, attackers can still spoof it. It checking PEB
	bool hades_isDebuggerPresent = Hades::WindowsAPI::IsDebuggerPresent();	//checking debugger present not recommented, attackers can still spoof it. It is checking PEB
	std::wstring hades_parentProcessName_nameOnly = L"**UNKNOWN**";
	std::wstring hades_parentProcessName_pathAndName = L"**UNKNOWN**";


	BOOL hadesRemoteDebug = FALSE;
	if (Hades::WindowsAPI::CheckRemoteDebuggerPresent(Hades::WindowsAPI::GetCurrentProcess(), &hadesRemoteDebug))
	{
		hades_checkRemoteDebuggerPresent = (bool)hadesRemoteDebug;
	}

	if (wchar_t* debugName = Hades::AntiDebug::GetParentProcessFileName(false)) //ensure is not nullptr. Get the name of PE file without the parent path
	{
		hades_parentProcessName_nameOnly = debugName;
		Hades::AntiDebug::FreeWstring(debugName); //this is the correct way to free the buffer allocated with Hades library
	}

	if (wchar_t* debugName = Hades::AntiDebug::GetParentProcessFileName(true)) //ensure is not nullptr. Get parent path with the name of the PE file
	{
		hades_parentProcessName_pathAndName = debugName;
		Hades::AntiDebug::FreeWstring(debugName); //this is the correct way to free the buffer allocated with Hades library
	}


	PrintBool("Hades - HasDetectedProcessDebugFlags", hades_hasDetectedProcessDebugFlags);
	PrintBool("Hades - HasDetectedProcessDebugObject", hades_hasDetectedProcessDebugObject);
	PrintBool("Hades - HasDetectedHardwareBreakpoints", hades_hasDetectedHardwareBreakpoints);
	PrintBool("Hades (WindowsAPI) - CheckRemoteDebuggerPresent", hades_checkRemoteDebuggerPresent);
	PrintBool("Hades (WindowsAPI) - IsDebuggerPresent", hades_isDebuggerPresent);
	std::wcout << "Hades - GetParentProcessFileName (without path): " << hades_parentProcessName_nameOnly << std::endl;
	std::wcout << "Hades - GetParentProcessFileName (with path): " << hades_parentProcessName_pathAndName << std::endl;

	return (
		hades_hasDetectedProcessDebugFlags || hades_hasDetectedProcessDebugObject ||
		hades_hasDetectedHardwareBreakpoints || hades_checkRemoteDebuggerPresent ||
		hades_isDebuggerPresent
	);

	// could also add this check but no need and we not want to flag non-debuggers as debugger justbecause opened by a other application:
	// hades_parentProcessName_nameOnly != L"explorer.exe"
}

// run the same checks as RunHadesChecks() but using Windows official headers-libraries directly, print result messages
void RunCommonChecks()
{
	PrintBool("Windows - HasDetectedProcessDebugFlags", Windows_HasDetectedProcessDebugFlags());
	PrintBool("Windows - HasDetectedProcessDebugObject", Windows_HasDetectedProcessDebugObject());
	PrintBool("Windows - HasDetectedHardwareBreakpoints", Windows_HasDetectedHardwareBreakpoints());

	BOOL normalRemoteDebug = FALSE;
	if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &normalRemoteDebug)) //call CheckRemoteDebuggerPresent normally
	{
		PrintBool("Windows - CheckRemoteDebuggerPresent", (bool)normalRemoteDebug);
	}

	PrintBool("Windows - IsDebuggerPresent", IsDebuggerPresent());

	if (wchar_t* debugName = Windows_GetParentProcessFileName())
	{
		std::wcout << "Windows - parent process name: " << debugName << std::endl;
		delete[] debugName;
	}
	else
	{
		std::wcout << "Windows - parent process name: " << L"**UNKNOWN**" << std::endl;
	}
}

int main()
{
	// Hades examples located located at RunHadesChecks().

	// This is a comparison between common anti-debug techniques by using Windows API without any library and same techniques by using Hades library.
	// Hades is able to bypass and detect any private or public debug-hide tool silently, without trigger and catch any exception at runtime.
	// This ensure that even if the hacker attach a debugger, will not cause halt of execution, so you can safely send an HTTP request to ban the user or terminate the debugger.
	// It can detect presence of usermode debuggers and special debuging tools which using VEH. There are however some not so common debugging technques like using page guard but
	// to detect this will need cause an exception. Will not provide this detection because if hacker attach any debugger this will halt the execution at a critical point, exposing
	// the location of all debug detections. If you still want to add extra detections, call them a long interval and away from Hades detections

	if (HWND consoleWindow = GetConsoleWindow())
	{
		SetWindowText(consoleWindow, TEXT("Try To Debug Me"));
	}
	
	bool hasBeenDetected = false;

	while (true)
	{
		system("cls"); //clear console

		if (hasBeenDetected)
		{
			SetGameOverColors();
			std::cout << ">> GAME OVER. YOU HAVE BEEN DETECTED! <<" << std::endl;
			std::cout << "      >> GOOD LUCK NEXT TIME <<" << std::endl << std::endl;
		}
		else
		{
			std::cout << "Nothing detected yet, but I'll keep an eye out for any suspicious activity." << std::endl << std::endl;
		}
		

		///////////////////////////////////////////////////////////////  HADES  ///////////////////////////////////////////////////////////////

		hasBeenDetected |= RunHadesChecks();

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		std::cout << std::endl << std::endl;

		////////////////////////////////////////////////////////////  WINDOWS  ////////////////////////////////////////////////////////////////
		
		RunCommonChecks();

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::cout << std::endl << std::endl;


		//a simple test to detect if a debugger-hide tool is currently used to hide the debugger
		bool windowsDetectedDebug = Windows_HasDetectedProcessDebugFlags() || Windows_HasDetectedProcessDebugObject();
		bool hadesDetectedDebug = Hades::AntiDebug::HasDetectedProcessDebugFlags() || Hades::AntiDebug::HasDetectedProcessDebugObject();

		if (hadesDetectedDebug && !windowsDetectedDebug)
		{
			std::cout << "Debugger-hide tool/s detected" << std::endl;
		}

		
		Sleep(1000); //pause execution for 1 second
	}
	return 0;
}
