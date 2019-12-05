#include "LuaClient.h"
#include <iostream>
#include <Windows.h>
#include "Logger.h"

LuaClient* LuaClient::m_instance = new LuaClient();
LuaClient::Garbage LuaClient::m_garbage;

LuaClient::LuaClient()
{
	// 创建虚拟栈
	m_pLuaState = luaL_newstate();	
	// 引入lua的标准库，不然调用print会报错，可以注释掉代码，查看报错
	luaL_openlibs(m_pLuaState);

	AddSearchPath();
}

LuaClient::~LuaClient()
{
	// 关闭虚拟栈
	lua_close(m_pLuaState);
}

void LuaClient::Start(const char* strStartLuaFile, const char* strEntryFunction)
{
	if (!m_pLuaState) return;

	BindCppToLua();

	// 将全局表压入栈中
	int result = luaL_dofile(m_pLuaState, strStartLuaFile);
	if (LUA_OK != result)
	{
		Logger::LogError("Error: %s", lua_tostring(m_pLuaState, -1));
		return;
	}

	lua_getglobal(m_pLuaState, strEntryFunction);

	// 调用指定的入口函数
	int argsNum = 0;		// 参数数量
	int resultsNum = 0;		// 返回值数量
	int errorFunc = 0;		// 错误处理函数在栈中的索引
	result = lua_pcall(m_pLuaState, argsNum, resultsNum, errorFunc);
	if (LUA_OK != result)
	{
		Logger::LogError("Error: %s", lua_tostring(m_pLuaState, -1));
		return;
	}
}

void LuaClient::DumpStack(bool bPrintTable)
{
	if (!m_pLuaState) return;

	Logger::SwitchColorToYellow();
	int top = lua_gettop(m_pLuaState);
	std::cout << "----------------------Stack Top----------------------" << std::endl;
	for (int i = top; i >= 1; --i)
	{
		int luaType = lua_type(m_pLuaState, i);
		switch (luaType)
		{
		case LUA_TNIL:
		{
			std::cout << "[" << i << "]: nil" << std::endl;
			break;
		}// For case LUA_TNIL

		case LUA_TBOOLEAN:
		{
			std::cout << "[" << i << "]: " << (lua_toboolean(m_pLuaState, i) ? "true" : "false") << std::endl;
			break;
		}// For case LUA_TBOOLEAN

		case LUA_TNUMBER:
		{
			std::cout << "[" << i << "]: " << lua_tonumber(m_pLuaState, i) << std::endl;
			break;
		}// For case LUA_TNUMBER

		case LUA_TSTRING:
		{
			std::cout << "[" << i << "]: " << lua_tostring(m_pLuaState, i) << std::endl;
			break;
		}// For case LUA_TSTRING

		case LUA_TTABLE:
		{
			if (bPrintTable)
			{
				std::cout << "[" << i << "]: " << lua_topointer(m_pLuaState, i) << std::endl;
				PrintTable(i);
			}
			else
				std::cout << "[" << i << "]: " << lua_typename(m_pLuaState, luaType)
				<< ": " << lua_topointer(m_pLuaState, i) << std::endl;
			break;
		}// For case LUA_TTABLE

		default:
			std::cout << "[" << i << "]: " << lua_typename(m_pLuaState, luaType)
				<< ": " << lua_topointer(m_pLuaState, i ) << std::endl;
			break;
		}// For switch (luaType)
	}// For end
	std::cout << "----------------------Stack Bottom----------------------" << std::endl;
	Logger::SwitchColorToWhite();
}

void LuaClient::AddSearchPath()
{
	char luaScriptPath[1000] = { 0 };
	bool bResult = GetScriptPath(luaScriptPath, 1000);
	if (!bResult) return;

	// 获取lua搜索路径
	lua_getglobal(m_pLuaState, "package");
	lua_pushstring(m_pLuaState, "path");
	lua_gettable(m_pLuaState, -2);
	const char* path = lua_tostring(m_pLuaState, -1);

	// 拼接新的lua搜索路径
	static char newPath[1000] = { 0 };
	strcpy_s(newPath, 1000, path);
	strcat_s(newPath, 1000, ";");
	strcat_s(newPath, 1000, luaScriptPath);

	// 重新设置lua搜索路径
	lua_pop(m_pLuaState, 1);
	lua_pushstring(m_pLuaState, "path");
	lua_pushstring(m_pLuaState, newPath);
	lua_settable(m_pLuaState, -3);

	// 恢复lua栈
	lua_pop(m_pLuaState, 1);
}

bool LuaClient::GetScriptPath(char* strOutPath, size_t length)
{
	if (nullptr == strOutPath) return false;

	// 获取exe的路径
	char exePath[1000] = { 0 };
	GetModuleFileName(NULL, exePath, 1000);

	// 获取当前解决方案的路径
	char* findChar = strstr(exePath, "bin");
	size_t copyLength = strlen(exePath) - strlen(findChar);
	if (length <= copyLength) return false;
	memcpy(strOutPath, exePath, copyLength);

	// 拼接lua脚本所在的相对路径
	strcpy_s(strOutPath + strlen(strOutPath), length - strlen(strOutPath), "Ryuujinn\\Script\\?.lua");

	return true;
}

void LuaClient::PrintTable(int index)
{
	std::cout << "{" << std::endl;

	if (m_pLuaState)
	{
		// 缓存之前的虚拟栈，因为后面要对虚拟栈进行操作
		int oldTop = lua_gettop(m_pLuaState);

		// 将需要输出的table压入栈顶
		lua_pushvalue(m_pLuaState, index);
		// 利用当前key(nil)值在进行遍历查找下一个key和value
		lua_pushnil(m_pLuaState);
		while (0 != lua_next(m_pLuaState, -2))
		{
			std::cout << "\t";
			// Stack     
			//				from bottom to top		from top to bottom
			// |  value |			3						-1
			// +--------+
			// |   key  |			2						-2
			// +--------+
			// |  table |			1						-3
			// +========+		
			int luaType = lua_type(m_pLuaState, -2);
			// 对key值进行处理
			{
				switch (luaType)
				{
				case LUA_TNIL:
				{
					std::cout << "nil";
					break;
				}// For case LUA_TNIL

				case LUA_TBOOLEAN:
				{
					std::cout << (lua_toboolean(m_pLuaState, -2) ? "true" : "false");
					break;
				}// For case LUA_TBOOLEAN

				case LUA_TNUMBER:
				{
					std::cout << lua_tonumber(m_pLuaState, -2);
					break;
				}// For case LUA_TNUMBER

				case LUA_TSTRING:
				{
					std::cout << lua_tostring(m_pLuaState, -2);
					break;
				}// For case LUA_TSTRING

				default:
					std::cout << lua_typename(m_pLuaState, luaType)
						<< ": " << lua_topointer(m_pLuaState, -2);
					break;
				}// For switch (luaType)
			}// Process key
			
			std::cout << "\t\t";
			// 对Value值进行处理
			{
				luaType = lua_type(m_pLuaState, -1);
				switch (luaType)
				{
				case LUA_TNIL:
				{
					std::cout << "nil" << std::endl;
					break;
				}// For case LUA_TNIL

				case LUA_TBOOLEAN:
				{
					std::cout << (lua_toboolean(m_pLuaState, -1) ? "true" : "false") << std::endl;
					break;
				}// For case LUA_TBOOLEAN

				case LUA_TNUMBER:
				{
					std::cout << lua_tonumber(m_pLuaState, -1) << std::endl;
					break;
				}// For case LUA_TNUMBER

				case LUA_TSTRING:
				{
					std::cout << lua_tostring(m_pLuaState, -1) << std::endl;
					break;
				}// For case LUA_TSTRING

				default:
					std::cout << lua_typename(m_pLuaState, luaType)
						<< ": " << lua_topointer(m_pLuaState, -1) << std::endl;
					break;
				}// For switch (luaType)
			}// Process value

			// 将Value从虚拟栈继续弹出，利用当前key值在进行遍历查找下一个key和value
			lua_pop(m_pLuaState, 1);
		}

		// 恢复成之前缓存的虚拟栈
		lua_settop(m_pLuaState, oldTop);
	}

	std::cout << "}" << std::endl;
}