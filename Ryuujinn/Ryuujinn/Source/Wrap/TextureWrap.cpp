#include "Texture.h"
#include <SDL.h>
#include <LuaClient.h>
#include <new>
#include "Logger.h"

int CreateTexture(lua_State* L)
{
	int count = lua_gettop(L);
	if (0 == count)
	{
		void* pointerToTexture = lua_newuserdata(L, sizeof(Texture));
		new (pointerToTexture)Texture();
	}
	else if(2 == count)
	{
		SDL_Renderer* pRenderer = (SDL_Renderer*)lua_touserdata(L, 1);
		const char* fileName = lua_tostring(L, 2);
		void* pointerToTexture = lua_newuserdata(L, sizeof(Texture));
		new (pointerToTexture)Texture(pRenderer, fileName);
	}
	else
		Logger::LogError("Error: Texture don't have the constructor have %d arguments.", count);
	
	luaL_getmetatable(L, "TextureMetaTable");
	lua_setmetatable(L, -2);

	return 1;
}

int DestroyTexture(lua_State* L)
{
	Texture* pTexture = (Texture*)lua_touserdata(L, 1);
	if (pTexture)
		pTexture->~Texture();

	return 0;
}

int RenderTexture(lua_State* L)
{
	int count = lua_gettop(L);

	Texture* pTexture = (Texture*)lua_touserdata(L, 1);
	SDL_Renderer* pRenderer = (SDL_Renderer*)lua_touserdata(L, 2);
	int x = (int)lua_tonumber(L, 3);
	int y = (int)lua_tonumber(L, 4);
	if (4 == count)
		pTexture->Render(pRenderer, x, y);
	else if(6 == count)
	{
		int width = (int)lua_tonumber(L, 5);
		int height = (int)lua_tonumber(L, 6);
		pTexture->Render(pRenderer, x, y, width, height);
	}

	return 0;
}

int TextureGet(lua_State* L)
{
	luaL_getmetatable(L, "TextureMetaTable");
	lua_pushvalue(L, 2);
	lua_rawget(L, -2);
	
	return 1;
}

void LuaWrap::RegisterTexture(lua_State* L)
{
	if (!L) return;

	lua_newtable(L);
	luaL_newmetatable(L, "TextureMetaTable");
	lua_pushstring(L, "New");
	lua_pushcfunction(L, CreateTexture);
	lua_rawset(L, -3);

	lua_pushstring(L, "__index");
	lua_pushcfunction(L, TextureGet);
	lua_rawset(L, -3);

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, DestroyTexture);
	lua_rawset(L, -3);

	lua_pushstring(L, "Render");
	lua_pushcfunction(L, RenderTexture);
	lua_rawset(L, -3);

	lua_setmetatable(L, -2);
	lua_setglobal(L, "Texture");
}