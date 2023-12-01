#pragma once

namespace Hades
{
	namespace HadesAPI
	{
		/*
		* Returns the file name of a process or nullptr if something went wrong.
		* process: handle of process.
		* copy: if this is false, it will return the buffer that Kernel allocated. If is true it will allocate and copy the string manually into a new buffer.
		* includeParentPath: whenever or not to return parent path with the file name or just the file name without path
		* When this function succeed it returns a address to a null-terminated unicode string, otherwise will return nullptr.
		* If copy is false, you can still read/write into the returned buffer, but anytime kernel can free it or change its content. Do not free this buffer manually.
		* If copy is true, it will automatically allocate and copy the file name into a new buffer. In this case make sure you free the buffer when you no need it anymore.
		* Output examples:
		*	with includeParentPath: "C:\\Users\\debug.exe"
		*	without includeParentPath: "debug.exe"
		*/
		wchar_t* GetProcessFileName(
			HANDLE process,
			bool copy = true,
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