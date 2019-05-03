#include "framework.h"
#include "cInjects.h"

bool injects::standard_inject_dll(HANDLE hProcess, const char* dllPath)
{

	if (!hProcess || hProcess == INVALID_HANDLE_VALUE || !dllPath)
		return false;
	auto dll_str = VirtualAllocEx(hProcess, nullptr, strlen(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!dll_str)
		return false;

	auto loadLibraryAddress = dll_str;
	if (!WriteProcessMemory(hProcess, dll_str, dllPath, strlen(dllPath), nullptr))
		goto theFail;

	loadLibraryAddress = GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
	if (!loadLibraryAddress)
		goto theFail;

	if (auto thandle = CreateRemoteThread(hProcess, nullptr, 0,
		reinterpret_cast<LPTHREAD_START_ROUTINE>(loadLibraryAddress), dll_str, 0, nullptr))
	{
		WaitForSingleObject(thandle, INFINITY);
		VirtualFreeEx(hProcess, dll_str, 0, MEM_COMMIT);
		return true;
	}

theFail:
	VirtualFreeEx(hProcess, dll_str, 0, MEM_COMMIT);
	return false;
}

