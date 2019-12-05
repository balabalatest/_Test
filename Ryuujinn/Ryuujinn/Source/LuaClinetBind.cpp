#include "LuaClient.h"
#include "Renderer.h"
#include "Logger.h"
#include "Texture.h"

void LuaClient::BindCppToLua()
{
	LuaWrap::RegisterLuaClient(m_pLuaState);
	LuaWrap::RegisterRenderer(m_pLuaState);
	LuaWrap::RegisterLogger(m_pLuaState);
	LuaWrap::RegisterTexture(m_pLuaState);
}