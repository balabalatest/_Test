#include "Renderer.h"

bool Renderer::Init(Uint32 flag)
{
	return 0 == SDL_Init(flag);
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