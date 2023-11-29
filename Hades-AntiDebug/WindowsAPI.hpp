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

        BOOL CheckRemoteDebuggerPresent(
            HANDLE hProcess,
            PBOOL pbDebuggerPresent
        );
    }
}