#include "pch.hpp"
#include "Kernel.hpp"
#include "WindowsAPI.hpp"
#include "HadesAPI.hpp"



wchar_t* Hades::HadesAPI::GetProcessFileName(HANDLE process, bool copy, bool includeParentPath)
{
	//this actually init UNICODE_STRING correctly.
	UNICODE_STRING name{};

	//ProcessImageFileNameWin32 returns a null-terminated unicode string. Also returns the same address everytime, so no need free anything.
	//Can edit the container of buffer freely but when ProcessImageFileNameWin32 re-called will replace the changes.
	if (Kernel::NtQueryInformationProcess(process, PROCESSINFOCLASS::ProcessImageFileNameWin32, &name, MAXSHORT, NULL) == STATUS_SUCCESS)
	{
		USHORT wcharsCount = name.Length / sizeof(wchar_t);

		if (wchar_t* resultWstr = (wchar_t*)name.Buffer)
		{
			if (copy)
			{
				if (resultWstr = new wchar_t[wcharsCount + 1])
				{
					for (USHORT x = 0; x != wcharsCount + 1; x++)
					{
						resultWstr[x] = name.Buffer[x];
					}
				}
				else
				{
					return nullptr;
				}
			}

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
