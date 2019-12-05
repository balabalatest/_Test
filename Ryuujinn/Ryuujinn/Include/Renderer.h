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
#pragma region 初始化
	static bool SDLInit(Uint32 flags);
	static bool SDLImageInit(int flags);
	static SDL_Window* CreateWindow(const char* title, int posX, int posY, int width, int hegiht, Uint32 flags);
	static SDL_Renderer* CreateRenderer(SDL_Window* pWindow, int index, Uint32 flags);
#pragma endregion

#pragma region 释放
	static void DestroyWindow(SDL_Window* pWindow);
	static void DestroyRenderer(SDL_Renderer* pRenderer);
	static void Quit();
#pragma endregion

#pragma region 报错
	static const char* GetError();
#pragma endregion

#pragma region 事件
	static bool PollEvent(SDL_Event& event);
#pragma endregion

#pragma region 时间
	static Uint32 GetTicks();
	static bool TICKS_PASSED(Uint32 currentTime, Uint32 targetTime);
#pragma endregion

#pragma region 渲染
	static void SetRenderDrawColor(SDL_Renderer* pRenderer, Uint8 r, Uint8 g, Uint8 b,
		Uint8 a);
	static void RenderClear(SDL_Renderer* pRenderer);
	static void RenderPresent(SDL_Renderer* pRenderer);
#pragma endregion

#pragma region 按钮
	static bool GetKeyboardState(int keycode);
#pragma endregion
};

struct lua_State;
namespace LuaWrap
{
	void RegisterRenderer(lua_State* L);
}