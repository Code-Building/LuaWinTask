#pragma once

class cRunLua
{
public:
	cRunLua();
	~cRunLua();
	void run_commands();
	bool execute_file(const char* thisFile);
	bool execute_script(const char* thisScript);
private:
	lua_State* L = nullptr;
	HANDLE tHandle = nullptr;
	bool loop = true;	
	void registers();
};

