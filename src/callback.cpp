/*
 * main.cpp
 *
 *  Created on: 2020年3月31日
 *      Author: root
 */

#include <iostream>
#include <stdio.h>
#ifdef __cplusplus
	#include "lua.hpp"
#else
	#include "lua.h"
	#include "lualib.h"
	#include "luaxlib.h"
#endif

void print_error(lua_State* state)
{
	// The error message is on top of the stack.
	// Fetch it, print it and then pop it off the stack.
	const char * message = lua_tostring(state,-1);
	puts(message);
	lua_pop(state,1);
}

void execute(const char *filename)
{
	lua_State *state = luaL_newstate();

	// Make standard libraries available in the lua object.
	luaL_openlibs(state);

	int result;

	// load the program; this supports both source code and bytecode files.
	result = luaL_loadfile(state, filename);

	if(result != LUA_OK)
	{
		print_error(state);
		return;
	}

	// Finally , execute the program by calling into it.
	// Change the arguments if you're not running vanilla Lua code.

	result = lua_pcall(state, 0, LUA_MULTRET, 0);

	if(result != LUA_OK)
	{
		print_error(state);
		return;
	}
}

#ifdef __cplusplus

extern "C"

{

int howdy(lua_State *state)
{
	// The number of function arguments will be on top of the stack
	int args = lua_gettop(state);

	printf("howdy() was called with %d arguments:\n", args);

	for(int i=1;i<args;i++)
	{
		printf("arguments %d: '%s'\n", n, lua_tostring(state, n) );
	}

	// Push the return value on top of the stack. NOTE: We haven't popped the
	// input arguments to our function. To be honest, I haven't checked if we
	// must, but at least in stack machines like the JVM. the stack will be
	// cleaned between each function call.

	lua_pushnumber(state, 123);

	// Let Lua know how many return values we've passed.
	return 1;
}

}

int main(int argc, char ** argv)
{
	if(argc <= 1)
	{
		puts("Usage: runlua file(s)");
		puts("Loads and excute Lua programs.");
		return 1;
	}

	// Execute all programes on the command line
	for(int n=1; n<argc;n++)
	{
		execute(argv[n]);
	}

	lua_State *state = luaL_newstate();
	lua_close(state);

	return 0;
}

