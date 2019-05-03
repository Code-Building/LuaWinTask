
#include "framework.h"
#include "Lua5.3.5/lua.hpp"
#include "cRunLua.h"
#define DllExport   extern "C" __declspec( dllexport )   

auto* runLua = new cRunLua();
DllExport bool runFile(const char* thisFile)
{
	runLua->execute_file(thisFile);
	return true;
}
DllExport bool runScript(const char* thisScript)
{
	runLua->execute_script(thisScript);
	return true;
}


