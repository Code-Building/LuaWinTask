#pragma once
class cProcess
{
public:
	cProcess();
	~cProcess();
	void updateList();
	std::uint32_t find(const wchar_t* proc);
	std::uint32_t findA(const char* proc);

	bool attach(const char* proc);
	bool attach(uint32_t id);
	void detach();
	HANDLE getHandle()
	{
		return this->hProcess;
	}
private:
	std::vector<PROCESSENTRY32W> pList = {};
	HANDLE hProcess = nullptr;
};

