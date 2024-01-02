#pragma once

namespace Hades
{
	namespace HadesAPI
	{
		/*
		* Returns the file name of a process or nullptr if something went wrong.
		* When the function succeed it returns a address to a null-terminated unicode string, otherwise will return nullptr.
		* You have to free the returned buffer with 'delete[]' when you done using it.
		* process: handle of process.
		* includeParentPath: whenever or not to return parent path with the file name or just the file name without path
		* Example:
		*		with includeParentPath: "C:\\Users\\debug.exe"
		*		without includeParentPath: "debug.exe"
		*/
		wchar_t* GetProcessFileName(
			HANDLE process,
			bool includeParentPath = true
		);


		/*
		* If succeed returns the id of process that opened the wanted process.
		*/
		DWORD GetParentProcessProcessId(HANDLE process);


		/*
		* If succeed returns the id of process that opened the current process.
		*/
		DWORD GetParentProcessProcessId();


	}
}