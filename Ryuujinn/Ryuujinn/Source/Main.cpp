#include "LuaClient.h"
#include <iostream>

int main()
{
	LuaClient::GetInstance()->Start("Script/Main.lua", "Main");

	system("pause");
	return 0;
}