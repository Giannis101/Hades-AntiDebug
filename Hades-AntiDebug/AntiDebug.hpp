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
		* Returns nullptr if failed, otherwise a buffer to the parent process file name. Don't forget to free the buffer
		* When a debugger open this application this can retrieve the file name of the debugger.
		* includeParentPath includes full path, else only the name of the file:
		*	with includeParentPath: "C:\\Users\\debug.exe"
		*	without includeParentPath: "debug.exe"
		*/
		wchar_t* GetParentProcessFileName(
			bool includeParentPath = true
		);

	}
}