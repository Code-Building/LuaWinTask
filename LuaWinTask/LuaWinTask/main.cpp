
#include "framework.h"
#include "Utils.hpp"
#include "Lua5.3.5/lua.hpp"

#define DllExport   extern "C" __declspec( dllexport )   

static int msgbox(lua_State* L)
{
	int parameterCount = lua_gettop(L);
	if (!parameterCount) return 0;

	const char* message = luaL_checkstring(L, 1);
	char titulo[] = "default";
	if (parameterCount == 2)
		memcpy(&titulo, luaL_checkstring(L, 2), sizeof(titulo));
	MessageBoxA(0, message, titulo, 0);
	return 0;
}

static int byCalc(lua_State * L)
{
	int parameterCount = lua_gettop(L); //pega a quantidade de argumentos passados
	if (parameterCount != 2) //defini um limite, que tem que ser 2 para essa função (obrigatorio)
		return 0; //se não for 2, zero retorno de valores
	auto var1 = luaL_checkinteger(L, 1); //pega o primeiro argumento que tem que ser numero
	auto var2 = luaL_checkinteger(L, 2); //pega o segundo argumento que tem que ser numero

	auto calc = uint32_t((var1 % var2) * 2);

	lua_pushinteger(L, calc); //joga para retorno da função

	return 1; //quantidade de retornos, no caso só tem 1 retorno
}



DllExport bool runLua(const char* thisFile)
{
	if (!thisFile)
		return false;
	lua_State* L = nullptr;
	L = luaL_newstate();
	if (L == nullptr)
		return false;

	luaL_openlibs(L);

	//registrando funções
	lua_register(L, "byCalc", byCalc);
	lua_register(L, "msgbox", msgbox);

	std::string thisStrFile(thisFile);
	if (!utils::is_file_exist(thisFile))
	{
		thisStrFile = (utils::get_path() + "\\" + thisStrFile);
		if (!utils::is_file_exist(thisStrFile.c_str()))
		{
			lua_close(L);
			return false;
		}
	}

	luaL_dofile(L, thisStrFile.c_str());
	lua_close(L);
	return true;
}