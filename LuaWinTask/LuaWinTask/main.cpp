
#include "framework.h"
#include "Lua5.3.5/lua.hpp"
#include "cRunLua.h"
#define DllExport   extern "C" __declspec( dllexport )   


void OpenConsole(std::string Title)
{
	FILE* stream;
	AllocConsole();
	freopen_s(&stream, "CONIN$", "r", stdin);
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONOUT$", "w", stderr);
	SetConsoleTitleA(Title.c_str());
}
auto* runLua = new cRunLua();
DllExport bool runFile(const char* thisFile, bool openconsole)
{
	if (openconsole)
		OpenConsole("");
	runLua->execute_file(thisFile);
	return true;
}
DllExport bool runScript(const char* thisScript, bool openconsole)
{
	if (openconsole)
		OpenConsole("");
	runLua->execute_script(thisScript);
	return true;
}
DllExport int rsti(const char* thisScript, const char* var, bool openconsole)
{
	if (openconsole)
		OpenConsole("");
	return runLua->e_r_script_integer(thisScript, var);
}

