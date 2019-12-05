#pragma once

#define SDL_MAIN_HANDLED

// ����SDL��Ҫ��ͷ�ļ�
#include <SDL.h>
#include <SDL_image.h>

// ����SDL��̬��
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")

class Renderer
{
public:
#pragma region ��ʼ��
	static bool SDLInit(Uint32 flags);
	static bool SDLImageInit(int flags);
	static SDL_Window* CreateWindow(const char* title, int posX, int posY, int width, int hegiht, Uint32 flags);
	static SDL_Renderer* CreateRenderer(SDL_Window* pWindow, int index, Uint32 flags);
#pragma endregion

#pragma region �ͷ�
	static void DestroyWindow(SDL_Window* pWindow);
	static void DestroyRenderer(SDL_Renderer* pRenderer);
	static void Quit();
#pragma endregion

#pragma region ����
	static const char* GetError();
#pragma endregion

#pragma region �¼�
	static bool PollEvent(SDL_Event& event);
#pragma endregion

#pragma region ʱ��
	static Uint32 GetTicks();
	static bool TICKS_PASSED(Uint32 currentTime, Uint32 targetTime);
#pragma endregion

#pragma region ��Ⱦ
	static void SetRenderDrawColor(SDL_Renderer* pRenderer, Uint8 r, Uint8 g, Uint8 b,
		Uint8 a);
	static void RenderClear(SDL_Renderer* pRenderer);
	static void RenderPresent(SDL_Renderer* pRenderer);
#pragma endregion

#pragma region ��ť
	static bool GetKeyboardState(int keycode);
#pragma endregion
};

struct lua_State;
namespace LuaWrap
{
	void RegisterRenderer(lua_State* L);
}