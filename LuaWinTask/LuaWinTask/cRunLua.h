#pragma once

class cRunLua
{
public:
	cRunLua();
	~cRunLua();
	void run_commands();
	bool execute_file(const char* thisFile);
	bool execute_script(const char* thisScript);

	/*
	"a,b = rpm('exec.exe',0x7ffff)", 'b';
	because: a return boolean and b return value
	it only works with integers
	*/
	int e_r_script_integer(const char* thisScript, const char* var);


private:
	lua_State* L = nullptr;
	HANDLE tHandle = nullptr;
	bool loop = true;	
	void registers();
};

