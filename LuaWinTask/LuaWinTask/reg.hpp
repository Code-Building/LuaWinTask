cProcess* process = new cProcess();
namespace reg
{

	static int inject_def(lua_State* L)
	{
		auto ret = false;
		int parameterCount = lua_gettop(L);
		if (parameterCount != 2)
		{
			lua_pushboolean(L, ret);
			return 1;
		}
		const char* procName = luaL_checkstring(L, 1);
		const char* fileName = luaL_checkstring(L, 2);

		process->updateList();
		if (process->attach(procName))
		{

			ret = injects::standard_inject_dll(process->getHandle(), fileName);
			process->detach();
		}

		lua_pushboolean(L, ret);
		return 1;
	}

	static int rpm(lua_State* L) {

		int pcount = lua_gettop(L);
		if (pcount >= 2) {
			int pid = 0;
			if (lua_isnumber(L, 1))
				pid = (int)luaL_checkinteger(L, 1);
			else
				pid = process->attach(luaL_checkstring(L, 1));

			DWORD addr = (DWORD)luaL_checkinteger(L, 2);
			std::vector<DWORD>offset;
			int valor = 0;
			if (pcount > 2) {
				for (int i = 1; i <= pcount - 2; ++i) {
					offset.push_back((DWORD)luaL_checkinteger(L, (i + 2)));
				}
			}
			uintptr_t test = process->FindDmaAddy(process->getHandle(), offset, addr);
			lua_pushboolean(L, ReadProcessMemory(process->getHandle(), (LPVOID)test, &valor, sizeof(valor), nullptr));
			lua_pushinteger(L, valor);
			return 2;
		}
		return 0;
	}


	static int wpm(lua_State* L) {

		uint32_t pCout = lua_gettop(L);
		if (pCout >= 2) {

			if (lua_isnumber(L, 1))
				process->attach(luaL_checkinteger(L, 1));
			else
				process->attach(luaL_checkstring(L, 1));

			DWORD addr = (DWORD)luaL_checkinteger(L, 2);
			std::vector<DWORD>offset;
			if (pCout > 3) {
				for (int i = 1; i <= pCout - 3; ++i) {
					offset.push_back((DWORD)luaL_checkinteger(L, (i + 2)));
				}
			}
			int valor = luaL_checkinteger(L,3);

			lua_pushboolean(L, WriteProcessMemory(process->getHandle(),(LPVOID)addr, &valor, sizeof(valor), nullptr));
			lua_pushinteger(L, valor);
			return 1;
		}
		return 0;
	}


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
}