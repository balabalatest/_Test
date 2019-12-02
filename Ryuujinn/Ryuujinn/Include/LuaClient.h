#pragma once

// ����lua��Ҫ��ͷ�ļ�
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

// ����Lua�������ɵľ�̬��
#pragma comment(lib, "Lua.lib")

class LuaClient
{
#pragma region Singleton ����������Garbage�����ͷ��ڴ�
public:
	static LuaClient* GetInstance() { return m_instance; }

private:
	class Garbage
	{
	public:
		~Garbage()
		{
			if (m_instance)
				delete m_instance;
			m_instance = nullptr;
		}
	};

private:
	static LuaClient* m_instance;
	static Garbage m_garbage;
#pragma endregion

private:
	LuaClient();
	virtual ~LuaClient();

public:
	/**
	 * Lua�ű����
	 * In ->  const char* strStartLuaFile		- ���Lua�ű�·��
	 *		  const char* strEntryFunction		- ��ں���
	 */
	void Start(const char* strStartLuaFile, const char* strEntryFunction);

	/**
	 * ����Cpp��lua
	 */
	void BindCppToLua();

	/**
	 * ���lua����ջ������
	 * In ->  bool bPrintTable					- �Ƿ����table���е�����
	 */
	void DumpStack(bool bPrintTable = false);

private:
	/**
	 * ���luaĿ¼
	 */
	void AddSearchPath();
	/**
	 * ��ȡLua ScriptĿ¼
	 */
	bool GetScriptPath(char* strOutPath, size_t length);

	/**
	 * ���lua����ջ��table������
	 * In ->  int index							- lua����ջ�е�����
	 */
	void PrintTable(int index);

private:
	lua_State* m_pLuaState;
};