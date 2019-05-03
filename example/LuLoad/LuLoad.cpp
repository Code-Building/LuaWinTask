#include <iostream>
#include <windows.h>
#include <stdio.h> 

int main()
{
	auto hmod = LoadLibrary(L"LuaWinTask.dll");
	if (!hmod) return 0;

	auto func = GetProcAddress(hmod, "runLua");
	if (!func) return 0;

	auto runLua = reinterpret_cast<bool(*)(const char* thisFile)>(func);
	if (runLua)
		runLua("main.lua");

	std::cout << "Hello World!\n";

	return getchar();
}
