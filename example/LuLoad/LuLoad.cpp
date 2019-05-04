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
	auto runFile = reinterpret_cast<bool(*)(const char* thisFile, bool openconsole)>(func);
	auto runScript = reinterpret_cast<bool(*)(const char* thisScript, bool openconsole)>(func2);

	if (runFile)
		runFile("main.lua", false);

	runScript(" print(\"runScript teste\") ", false); // Ta dando erro.
	std::cout << "Hello World!\n";
	//runScript("rpm(\"citra-qt.exe\",0x1ABDDEBC) ", false);

	return getchar();
}
