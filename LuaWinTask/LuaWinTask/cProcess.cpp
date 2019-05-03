#include "framework.h"
#include "cProcess.h"



void cProcess::updateList()
{
	pList.clear();
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	auto pe = PROCESSENTRY32W{ sizeof(PROCESSENTRY32W) };

	if (Process32FirstW(snapshot, &pe)) {
		do {
			pList.push_back(pe);
		} while (Process32NextW(snapshot, &pe));
	}
	CloseHandle(snapshot);
}

cProcess::cProcess()
{
	updateList();
}

cProcess::~cProcess()
{
	pList.clear();
}

std::uint32_t cProcess::find(const wchar_t* proc)
{
	if (!proc) return 0;
	for (auto& p : pList)
		if (!_wcsicmp(proc, p.szExeFile))
			return p.th32ProcessID;	
	return 0;
}

const wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	size_t pRet = 0;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs_s(&pRet, wc, cSize, c, cSize-1);
	return wc;
}
std::uint32_t cProcess::findA(const char* proc)
{
	return find(GetWC(proc));
}

bool cProcess::attach(uint32_t id)
{
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, id);
	return (hProcess && hProcess != INVALID_HANDLE_VALUE);
}

bool cProcess::attach(const char* proc)
{
	auto id = findA(proc);
	if (!id) return false;
	return attach(id);
}

void cProcess::detach()
{
	CloseHandle(hProcess);
}