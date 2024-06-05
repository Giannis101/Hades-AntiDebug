#include "pch.hpp"
#include "Kernel.hpp"
#include "WindowsAPI.hpp"
#include "HadesAPI.hpp"



wchar_t* Hades::HadesAPI::GetProcessFileName(HANDLE process, bool includeParentPath)
{
	//this looks like it works... ProcessImageFileNameWin32 has to write in stack for some reason.
	WCHAR stackBuffer[MAX_PATH + 1] = { L'\0' };
	UNICODE_STRING name = { 0, sizeof(stackBuffer), stackBuffer };
	
	//ProcessInformationLength is the total size of (UNICODE_STRING + stackBuffer) in bytes.
	//It will zero the buffer automatically before write to it, so the string will be null-terminated.
	if (Kernel::NtQueryInformationProcess(process, PROCESSINFOCLASS::ProcessImageFileNameWin32, &name, sizeof(stackBuffer) + sizeof(UNICODE_STRING), NULL) == STATUS_SUCCESS)
	{
		USHORT wcharsCount = name.Length / sizeof(wchar_t);

		if (name.Buffer && wcharsCount)
		{
			if (wchar_t* resultWstr = new wchar_t[3 * wcharsCount + 1])
			{
				//copy buffer
				for (USHORT x = 0; x != wcharsCount + 1; x++)
				{
					resultWstr[x] = name.Buffer[x];
				}

				//remove parent path if need
				if (!includeParentPath)
				{
					for (int x = wcharsCount; x != -1; x--)
					{
						if (resultWstr[x] == L'/' || resultWstr[x] == L'\\')
						{
							USHORT delta = (USHORT)x + 1;
							USHORT len = wcharsCount - (USHORT)x;
							for (USHORT nx = 0ui16; nx != len; nx++)
							{
								resultWstr[nx] = resultWstr[delta + nx];
							}

							break;
						}
					}
				}

				return resultWstr;
			}
		}
	}

	return nullptr;
}

DWORD Hades::HadesAPI::GetParentProcessProcessId(HANDLE process)
{   
	PROCESS_BASIC_INFORMATION info{};
	if (Kernel::NtQueryInformationProcess(process, PROCESSINFOCLASS::ProcessBasicInformation, &info, sizeof(PROCESS_BASIC_INFORMATION), nullptr) == STATUS_SUCCESS)
	{
		return (DWORD)info.InheritedFromUniqueProcessId;
	}

	return 0;
}

DWORD Hades::HadesAPI::GetParentProcessProcessId()
{
	return GetParentProcessProcessId(Kernel::NtCurrentProcess());
}

void Hades::HadesAPI::FreeWstring(wchar_t* wStr)
{
	if (wStr) delete wStr;
}
