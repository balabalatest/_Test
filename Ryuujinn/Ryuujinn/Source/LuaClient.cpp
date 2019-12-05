#include "LuaClient.h"
#include <iostream>
#include <Windows.h>
#include "Logger.h"

LuaClient* LuaClient::m_instance = new LuaClient();
LuaClient::Garbage LuaClient::m_garbage;

LuaClient::LuaClient()
{
	// ��������ջ
	m_pLuaState = luaL_newstate();	
	// ����lua�ı�׼�⣬��Ȼ����print�ᱨ������ע�͵����룬�鿴����
	luaL_openlibs(m_pLuaState);

	AddSearchPath();
}

LuaClient::~LuaClient()
{
	// �ر�����ջ
	lua_close(m_pLuaState);
}

void LuaClient::Start(const char* strStartLuaFile, const char* strEntryFunction)
{
	if (!m_pLuaState) return;

	BindCppToLua();

	// ��ȫ�ֱ�ѹ��ջ��
	int result = luaL_dofile(m_pLuaState, strStartLuaFile);
	if (LUA_OK != result)
	{
		Logger::LogError("Error: %s", lua_tostring(m_pLuaState, -1));
		return;
	}

	lua_getglobal(m_pLuaState, strEntryFunction);

	// ����ָ������ں���
	int argsNum = 0;		// ��������
	int resultsNum = 0;		// ����ֵ����
	int errorFunc = 0;		// ����������ջ�е�����
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

	// ��ȡlua����·��
	lua_getglobal(m_pLuaState, "package");
	lua_pushstring(m_pLuaState, "path");
	lua_gettable(m_pLuaState, -2);
	const char* path = lua_tostring(m_pLuaState, -1);

	// ƴ���µ�lua����·��
	static char newPath[1000] = { 0 };
	strcpy_s(newPath, 1000, path);
	strcat_s(newPath, 1000, ";");
	strcat_s(newPath, 1000, luaScriptPath);

	// ��������lua����·��
	lua_pop(m_pLuaState, 1);
	lua_pushstring(m_pLuaState, "path");
	lua_pushstring(m_pLuaState, newPath);
	lua_settable(m_pLuaState, -3);

	// �ָ�luaջ
	lua_pop(m_pLuaState, 1);
}

bool LuaClient::GetScriptPath(char* strOutPath, size_t length)
{
	if (nullptr == strOutPath) return false;

	// ��ȡexe��·��
	char exePath[1000] = { 0 };
	GetModuleFileName(NULL, exePath, 1000);

	// ��ȡ��ǰ���������·��
	char* findChar = strstr(exePath, "bin");
	size_t copyLength = strlen(exePath) - strlen(findChar);
	if (length <= copyLength) return false;
	memcpy(strOutPath, exePath, copyLength);

	// ƴ��lua�ű����ڵ����·��
	strcpy_s(strOutPath + strlen(strOutPath), length - strlen(strOutPath), "Ryuujinn\\Script\\?.lua");

	return true;
}

void LuaClient::PrintTable(int index)
{
	std::cout << "{" << std::endl;

	if (m_pLuaState)
	{
		// ����֮ǰ������ջ����Ϊ����Ҫ������ջ���в���
		int oldTop = lua_gettop(m_pLuaState);

		// ����Ҫ�����tableѹ��ջ��
		lua_pushvalue(m_pLuaState, index);
		// ���õ�ǰkey(nil)ֵ�ڽ��б���������һ��key��value
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
			// ��keyֵ���д���
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
			// ��Valueֵ���д���
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

			// ��Value������ջ�������������õ�ǰkeyֵ�ڽ��б���������һ��key��value
			lua_pop(m_pLuaState, 1);
		}

		// �ָ���֮ǰ���������ջ
		lua_settop(m_pLuaState, oldTop);
	}

	std::cout << "}" << std::endl;
}