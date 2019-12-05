#include "Renderer.h"
#include "Logger.h"

bool Renderer::SDLInit(Uint32 flags)
{
	return 0 == SDL_Init(flags);
}

bool Renderer::SDLImageInit(int flags)
{
	return 0 != IMG_Init(IMG_INIT_PNG);
}

SDL_Window* Renderer::CreateWindow(const char* title, int posX, int posY, int width, int hegiht, Uint32 flags)
{
	return SDL_CreateWindow(title, posX, posY, width, hegiht, flags);
}

SDL_Renderer* Renderer::CreateRenderer(SDL_Window* pWindow, int index, Uint32 flags)
{
	return SDL_CreateRenderer(pWindow, index, flags);
}

void Renderer::DestroyWindow(SDL_Window* pWindow)
{
	if (pWindow)
		SDL_DestroyWindow(pWindow);
}

void Renderer::DestroyRenderer(SDL_Renderer* pRenderer)
{
	if (pRenderer)
		SDL_DestroyRenderer(pRenderer);
}

void Renderer::Quit()
{
	SDL_Quit();
}

const char* Renderer::GetError()
{
	return SDL_GetError();
}

bool Renderer::PollEvent(SDL_Event& event)
{
	return SDL_PollEvent(&event);
}

Uint32 Renderer::GetTicks()
{
	return SDL_GetTicks();
}

bool Renderer::TICKS_PASSED(Uint32 currentTime, Uint32 targetTime)
{
	return SDL_TICKS_PASSED(currentTime, targetTime);
}

void Renderer::SetRenderDrawColor(SDL_Renderer* pRenderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(pRenderer, r, g, b, a);
}

void Renderer::RenderClear(SDL_Renderer* pRenderer)
{
	SDL_RenderClear(pRenderer);
}

void Renderer::RenderPresent(SDL_Renderer* pRenderer)
{
	SDL_RenderPresent(pRenderer);
}

bool Renderer::GetKeyboardState(int keycode)
{
	bool bResult = false;
	const Uint8* pState = SDL_GetKeyboardState(nullptr);
	if (pState)
		bResult = pState[keycode];

	return bResult;
}