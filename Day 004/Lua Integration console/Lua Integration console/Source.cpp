// LUA
//#include <iostream>
#include "lua.hpp"
//using namespace std;
//#pragma comment(lib, "lua5.1.lib")

int main()
{
	// LUA
	// Create and start lua environment
	lua_State *Env = lua_open();
	// To load libs
	luaL_openlibs(Env);
	// Run our "hello.lua" file
	if (luaL_dofile(Env, "Hello World.lua"))
	{
		const char* err = lua_tostring(Env, -1);
		printf(err);
	}
	// Close your environment
	lua_close(Env);
	// get a character from the user
	getchar();
	//return 0 if there is no error
	return 0;

}