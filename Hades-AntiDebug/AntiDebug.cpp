#include "pch.hpp"
#include "Kernel.hpp"
#include "AntiDebug.hpp"



bool Hades::AntiDebug::HasDetectedProcessDebugFlags()
{
    return HasDetectedProcessDebugFlags(Hades::Kernel::NtCurrentProcess());
}

bool Hades::AntiDebug::HasDetectedProcessDebugObject()
{
    return HasDetectedProcessDebugObject(Hades::Kernel::NtCurrentProcess());
}

bool Hades::AntiDebug::HasDetectedProcessDebugFlags(HANDLE process)
{
    ULONG debugFlags = 0;
    if (Hades::Kernel::NtQueryInformationProcess(Hades::Kernel::NtCurrentProcess(), Hades::PROCESSINFOCLASS::ProcessDebugFlags, &debugFlags, sizeof(ULONG), NULL) == STATUS_SUCCESS)
    {
        if (debugFlags == 0) return true;
    }

    HANDLE debugHandle = NULL;
    if (Hades::Kernel::NtQueryInformationProcess(Hades::Kernel::NtCurrentProcess(), Hades::PROCESSINFOCLASS::ProcessDebugObjectHandle, &debugHandle, sizeof(HANDLE), NULL) == STATUS_SUCCESS)
    {
        if (debugHandle != NULL) return true;
    }

    return false;
}

bool Hades::AntiDebug::HasDetectedProcessDebugObject(HANDLE process)
{
    HANDLE debugHandle = NULL;
    if (Hades::Kernel::NtQueryInformationProcess(Hades::Kernel::NtCurrentProcess(), Hades::PROCESSINFOCLASS::ProcessDebugObjectHandle, &debugHandle, sizeof(HANDLE), NULL) == STATUS_SUCCESS)
    {
        if (debugHandle != NULL) return true;
    }

    return false;
}