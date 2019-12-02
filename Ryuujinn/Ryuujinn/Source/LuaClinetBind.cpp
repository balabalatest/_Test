#include "LuaClient.h"
#include "Renderer.h"
#include "Logger.h"

void LuaClient::BindCppToLua()
{
	LuaWrap::RegisterRenderer(m_pLuaState);
	LuaWrap::RegisterLogger(m_pLuaState);
}