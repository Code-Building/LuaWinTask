#include "framework.h"
#include "cProcess.h"
#include "Utils.hpp"
#include "cInjects.h"
#include "Lua5.3.5/lua.hpp"
#include "cRunLua.h"
#include "reg.hpp"

void LoopLua(cRunLua * _this)
{
	_this->run_commands();
}

bool cRunLua::execute_file(const char* thisFile)
{
	if (!thisFile)
		return false;
	std::string thisStrFile(thisFile);
	if (thisStrFile.find("\\") == std::string::npos)
	{
		thisStrFile = (utils::get_path() + "\\" + thisStrFile);
		if (!utils::is_file_exist(thisStrFile.c_str()))
		{
			lua_close(L);
			return false;
		}
	}
	luaL_dofile(L, thisStrFile.c_str());
}

bool cRunLua::execute_script(const char* thisScript)
{
	if (!thisScript)
		return false;
	luaL_dostring(L, thisScript);
}

void cRunLua::run_commands()
{
	printf("run_commands\n");
	while (this->loop)	
		Sleep(5000);
}

void cRunLua::registers()
{
	//registrando funções
	lua_register(L, "byCalc",		reg::byCalc); //example
	lua_register(L, "msgbox",		reg::msgbox); //example
	lua_register(L, "inject_def",	reg::inject_def);
}

cRunLua::cRunLua()
{
	L = luaL_newstate();
	if (!L) return;
	luaL_openlibs(L);
	registers();
	if (!tHandle)
		tHandle = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoopLua), this, 0, nullptr);
}

cRunLua::~cRunLua()
{
	TerminateThread(tHandle, -1);
	lua_close(L);
}
