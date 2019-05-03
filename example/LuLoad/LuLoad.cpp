#include <iostream>
#include <windows.h>
#include <stdio.h> 

int main()
{
	auto hmod = LoadLibrary(L"LuaWinTask.dll");
	if (!hmod) return 0;

	auto func = GetProcAddress(hmod, "runFile");
	if (!func) return 0;
	auto func2 = GetProcAddress(hmod, "runScript");
	auto runFile = reinterpret_cast<bool(*)(const char* thisFile)>(func);
	auto runScript = reinterpret_cast<bool(*)(const char* thisScript)>(func2);

	if (runFile)
		runFile("main.lua");

	runScript(" print(\"runScript teste\") ");
	std::cout << "Hello World!\n";

	return getchar();
}
