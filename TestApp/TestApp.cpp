#include <iostream>
#include <Windows.h>

#pragma comment (lib, "../x64/Release/Hades-AntiDebug.lib")    //include Hades anti-debugging library

//#include "../Hades-AntiDebug/Kernel.hpp"      //include this only if you want access kernel functions (Hades::Kernel). Otherwise no need.
#include "../Hades-AntiDebug/WindowsAPI.hpp"    //include this only if you want use Windows API functions throu Hades (Hades::WindowsAPI). Otherwise no need.
#include "../Hades-AntiDebug/AntiDebug.hpp"     //include this if want to use Hades::AntiDebug functions



void PrintBool(const char* description, bool result)
{
	std::cout << description << " : " << (result ? "YES" : "NO") << std::endl;
}

int main()
{
	while (true)
	{
		std::cout << "Checking if debugger is present in this process" << std::endl << std::endl;

		///////////////////////////////////////////////////////////////  HADES  ///////////////////////////////////////////////////////////////
		PrintBool("Hades - HasDetectedProcessDebugFlags: ", Hades::AntiDebug::HasDetectedProcessDebugFlags());
		PrintBool("Hades - HasDetectedProcessDebugObject: ", Hades::AntiDebug::HasDetectedProcessDebugObject());

		BOOL hadesRemoteDebug = FALSE;
		if (Hades::WindowsAPI::CheckRemoteDebuggerPresent(GetCurrentProcess(), &hadesRemoteDebug)) //call CheckRemoteDebuggerPresent with Hades
		{
			PrintBool("Hades (WindowsAPI) - HasDetectedProcessDebugObject: ", (bool)hadesRemoteDebug);
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




		////////////////////////////////////////////////////////////  WINDOWS  ////////////////////////////////////////////////////////////////
		BOOL normalRemoteDebug = FALSE;
		if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &normalRemoteDebug)) //call CheckRemoteDebuggerPresent normally
		{
			PrintBool("Windows - HasDetectedProcessDebugObject: ", (bool)normalRemoteDebug);
		}

		PrintBool("Windows - IsDebuggerPresent: ", IsDebuggerPresent());
		////////////////////////////////////////////////////////////  WINDOWS  ////////////////////////////////////////////////////////////////
	
		
		Sleep(1000);
		system("cls"); //clear console
	}
	return 0;
}
