#include "Logger.h"
#include "LuaClient.h"
#include <iostream>

int SwtichColorToRed(lua_State* L)
{
	Logger::SwtichColorToRed();

	return 0;
}

int SwitchColorToYellow(lua_State* L)
{
	Logger::SwitchColorToYellow();

	return 0;
}

int SwitchColorToWhite(lua_State* L)
{
	Logger::SwitchColorToWhite();

	return 0;
}

int LoggerGet(lua_State* L)
{
	const char* strKey = lua_tostring(L, 2);

	luaL_getmetatable(L, "LoggerMetaTable");
	lua_pushvalue(L, 2);
	lua_rawget(L, -2);
	if (lua_isnil(L, -1))
		Logger::LogError("Logger don't have the field: %s.\n%s:%d: in function '%s'", strKey, __FILE__, __LINE__, __FUNCTION__);

	return 1;
}

int LoggerSet(lua_State* L)
{
	luaL_getmetatable(L, "LoggerMetaTable");
	lua_pushvalue(L, 2);
	lua_rawget(L, -2);
	if (lua_isnil(L, -1))
	{
		lua_pop(L, 1);
		lua_pushvalue(L, 2);
		lua_pushvalue(L, 3);
		lua_rawset(L, -3);
	}
	else
	{
		if (LUA_TFUNCTION == lua_type(L, -1))
			Logger::LogError("The action is not allowed.\n%s:%d: in function '%s'", __FILE__, __LINE__, __FUNCTION__);
		else
		{
			lua_pop(L, 1);
			lua_pushvalue(L, 2);
			lua_pushvalue(L, 3);
			lua_rawset(L, -3);
		}
	}

	return 0;
}

void LuaWrap::RegisterLogger(lua_State* L)
{
	if (!L) return;

	lua_newtable(L);

	luaL_newmetatable(L, "LoggerMetaTable");
	lua_pushstring(L, "__index");
	lua_pushcfunction(L, LoggerGet);
	lua_rawset(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, LoggerSet);
	lua_rawset(L, -3);

	lua_pushstring(L, "SwtichColorToRed");
	lua_pushcfunction(L, SwtichColorToRed);
	lua_rawset(L, -3);

	lua_pushstring(L, "SwitchColorToYellow");
	lua_pushcfunction(L, SwitchColorToYellow);
	lua_rawset(L, -3);

	lua_pushstring(L, "SwitchColorToWhite");
	lua_pushcfunction(L, SwitchColorToWhite);
	lua_rawset(L, -3);

	lua_setmetatable(L, -2);
	lua_setglobal(L, "Logger");
}