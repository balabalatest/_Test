#pragma once

#define SDL_MAIN_HANDLED

// 引入SDL需要的头文件
#include <SDL.h>
#include <SDL_image.h>

// 链接SDL静态库
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")

class Renderer
{
public:
	static bool Init(Uint32 flag);
	static SDL_Window* CreateWindow(const char* title, int posX, int posY, int width, int hegiht, Uint32 flags);
	static SDL_Renderer* CreateRenderer(SDL_Window* pWindow, int index, Uint32 flags);

	static void DestroyWindow(SDL_Window* pWindow);
	static void DestroyRenderer(SDL_Renderer* pRenderer);
	static void Quit();
};

struct lua_State;
namespace LuaWrap
{
	void RegisterRenderer(lua_State* L);
}