#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Logger.h"

Texture::Texture()
{
	m_pSDLTexture = nullptr;
	m_textureWidth = 0;
	m_textureHeight = 0;
}

Texture::Texture(SDL_Renderer* pRenderer, const char* fileName)
{
	SDL_Surface* pSurface = IMG_Load(fileName);
	if (!pSurface)
	{
		Logger::LogError("IMG_Load() failed in Renderer::GetTexture(): %s", fileName);
		return;
	}

	m_pSDLTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	SDL_FreeSurface(pSurface);
	if (!m_pSDLTexture)
	{
		Logger::LogError("SDL_CreateTextureFromSurface() failed in GetTexture(): %s", SDL_GetError());
		return;
	}

	QueryTexture();
}

Texture::~Texture()
{
	if (m_pSDLTexture)
	{
		SDL_DestroyTexture(m_pSDLTexture);
		m_pSDLTexture = nullptr;
	}
}

void Texture::Render(SDL_Renderer* pRenderer, int x, int y)
{
	if (nullptr == pRenderer || nullptr == m_pSDLTexture) return;

	SDL_Rect destination;
	destination.w = m_textureWidth;
	destination.h = m_textureHeight;
	destination.x = x;
	destination.y = y;

	SDL_RenderCopy(pRenderer, m_pSDLTexture, nullptr, &destination);
}

void Texture::Render(SDL_Renderer* pRenderer, int x, int y, int width, int height)
{
	if (nullptr == pRenderer || nullptr == m_pSDLTexture) return;

	if (nullptr == pRenderer || nullptr == m_pSDLTexture) return;

	SDL_Rect destination;
	destination.w = width;
	destination.h = height;
	destination.x = x;
	destination.y = y;

	SDL_RenderCopy(pRenderer, m_pSDLTexture, nullptr, &destination);
}

void Texture::QueryTexture()
{
	if (m_pSDLTexture)
		SDL_QueryTexture(m_pSDLTexture, nullptr, nullptr, &m_textureWidth, &m_textureHeight);
}