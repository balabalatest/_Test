#include "Renderer.h"
#include <LuaClient.h>
#include "Logger.h"

int Init(lua_State* L)
{
	Uint32 flag = (Uint32)lua_tointeger(L, 1);
	lua_pushboolean(L, Renderer::Init(flag));

	return 1;
}

int CreateWindow(lua_State* L)
{
	const char* title = lua_tostring(L, 1);
	int posX = (int)lua_tointeger(L, 2);
	int posY = (int)lua_tointeger(L, 3);
	int width = (int)lua_tointeger(L, 4);
	int hegiht = (int)lua_tointeger(L, 5);
	Uint32 flag = (Uint32)lua_tointeger(L, 6);
	lua_pushlightuserdata(L, Renderer::CreateWindow(title, posX, posY, width, hegiht, flag));

	return 1;
}

int CreateRenderer(lua_State* L)
{
	SDL_Window* pWindow = (SDL_Window*)lua_touserdata(L, 1);
	int index = (int)lua_tointeger(L, 2);
	Uint32 flag = (Uint32)lua_tointeger(L, 3);
	lua_pushlightuserdata(L, Renderer::CreateRenderer(pWindow, index, flag));

	return 1;
}

int DestroyWindow(lua_State* L)
{
	SDL_Window* pWindow = (SDL_Window*)lua_touserdata(L, 1);
	Renderer::DestroyWindow(pWindow);

	return 0;
}

int DestroyRenderer(lua_State* L)
{
	SDL_Renderer* pRenderer = (SDL_Renderer*)lua_touserdata(L, 1);
	Renderer::DestroyRenderer(pRenderer);

	return 0;
}

int Quit(lua_State* L)
{
	Renderer::Quit();

	return 0;
}

int RendererGet(lua_State* L)
{
	const char* strKey = lua_tostring(L, 2);

	luaL_getmetatable(L, "RendererMetaTable");
	lua_pushvalue(L, 2);
	lua_rawget(L, -2);
	if (lua_isnil(L, -1))
		Logger::LogError("Renderer don't have the field: %s.\n%s:%d: in function '%s'", strKey, __FILE__, __LINE__, __FUNCTION__);

	return 1;
}

int RendererSet(lua_State* L)
{
	luaL_getmetatable(L, "RendererMetaTable");
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
		if(LUA_TFUNCTION == lua_type(L, -1))
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

void LuaWrap::RegisterRenderer(lua_State* L)
{
	if (!L) return;

	lua_newtable(L);

	luaL_newmetatable(L, "RendererMetaTable");
	lua_pushstring(L, "__index");
	lua_pushcfunction(L, RendererGet);
	lua_rawset(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, RendererSet);
	lua_rawset(L, -3);

	lua_pushstring(L, "Init");
	lua_pushcfunction(L, Init);
	lua_rawset(L, -3);

	lua_pushstring(L, "CreateWindow");
	lua_pushcfunction(L, CreateWindow);
	lua_rawset(L, -3);

	lua_pushstring(L, "CreateRenderer");
	lua_pushcfunction(L, CreateRenderer);
	lua_rawset(L, -3);

	lua_pushstring(L, "DestroyWindow");
	lua_pushcfunction(L, DestroyWindow);
	lua_rawset(L, -3);

	lua_pushstring(L, "DestroyRenderer");
	lua_pushcfunction(L, DestroyRenderer);
	lua_rawset(L, -3);

	lua_pushstring(L, "Quit");
	lua_pushcfunction(L, Quit);
	lua_rawset(L, -3);

	lua_setmetatable(L, -2);
	lua_setglobal(L, "Renderer");
}