#include <string>


namespace Hades
{
	namespace AntiDebug
	{
		/*
		* Returns true if debugger detected.
		* Silent checks, not throwing exceptions.
		* Checking for debugging flags in self process.
		*/
		bool HasDetectedProcessDebugFlags();


		/*
		* Returns true if debugger detected.
		* Silent checks, not throwing exceptions.
		* Checking for debugging object handle in self process.
		*/
		bool HasDetectedProcessDebugObject();


		/*
		* Returns true if debugger detected.
		* process: handle of remote process.
		* Silent checks, not throwing exceptions.
		* Checking for debugging flags in remote process.
		*/
		bool HasDetectedProcessDebugFlags(
			HANDLE process
		);


		/*
		* Returns true if debugger detected.
		* process: handle of remote process.
		* Silent checks, not throwing exceptions.
		* Checking for debugging object handle in remote process.
		*/
		bool HasDetectedProcessDebugObject(
			HANDLE process
		);


		/*
		* Returns true if any hardware or software (INT3) breakpoint detected in local application.
		* Silent checks, not throwing exceptions.
		*/
		bool HasDetectedHardwareBreakpoints();


		/*
		* Returns nullptr if failed, otherwise a buffer to the parent process file name. Don't forget to free the buffer
		* Can retrieve the file name of the debugger.
		* includeParentPath includes full path, else only the name of the file:
		*	with includeParentPath: "C:\\Users\\debug.exe"
		*	without includeParentPath: "debug.exe"
		* If a debugger open this application, this function will get its file name. explorer.exe is the defaul when no debugger used.
		* Avoid using this to debug if application is debugged. Use it only as an optional information for your logs.
		* Silent checks, not throwing exceptions.
		*/
		wchar_t* GetParentProcessFileName(
			bool includeParentPath = true
		);


		/*
		* Returns nullptr if failed, otherwise a buffer to the parent process file name. Don't forget to free the buffer
		* Can retrieve the file name of the debugger.
		* includeParentPath includes full path, else only the name of the file:
		*	with includeParentPath: "C:\\Users\\debug.exe"
		*	without includeParentPath: "debug.exe"
		* If a debugger open the target application, this function will get its file name. explorer.exe is the defaul when no debugger used.
		* Avoid using this to debug if application is debugged. Use it only as an optional information for your logs.
		* Silent checks, not throwing exceptions.
		*/
		wchar_t* GetParentProcessFileName(
			HANDLE process,
			bool includeParentPath = true
		);


		/*
		* Returns true if termination request succeed, otherwise it returns false.
		* exitCode is the process exit reason.
		* Can use this function to termintate the debugger process that debugging the current application.
		* Should check if the parent is not explorer.exe, as may cause problem if close a windows process.
		* Silent, not throwing exceptions and cannot debugged and found easy.
		*/
		bool TerminateParentProcess(
			int exitCode = 0
		);


		/*
		* Returns true if termination request succeed, otherwise it returns false.
		* exitCode is the process exit reason.
		* Can use this function to termintate the debugger process that debugging the current application.
		* Should check if the parent is not explorer.exe, as may cause problem if close a windows process.
		* Silent, not throwing exceptions and cannot debugged and found easy.
		*/
		bool TerminateParentProcess(
			HANDLE process,
			int exitCode = 0
		);


		/*
		* Close instantly the currect application.
		* exitCode is the exit reason.
		* Silent, not throwing exceptions and cannot debugged and found easy.
		*/
		void TerminateCurrentProcess(
			int exitCode = 0
		);
	}
}