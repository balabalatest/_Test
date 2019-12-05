#include "LuaClient.h"

int DumpStack(lua_State* L)
{
	bool bPrintTable = 1 == lua_toboolean(L, 1);
	LuaClient::GetInstance()->DumpStack(bPrintTable);

	return 0;
}

void LuaWrap::RegisterLuaClient(lua_State* L)
{
	lua_pushcfunction(L, DumpStack);
	lua_setglobal(L, "DumpStack");
}