#pragma once

// 引入lua需要的头文件
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

// 链接Lua工程生成的静态库
#pragma comment(lib, "Lua.lib")

class LuaClient
{
#pragma region Singleton 单例，利用Garbage类来释放内存
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
	 * Lua脚本入口
	 * In ->  const char* strStartLuaFile		- 入口Lua脚本路径
	 *		  const char* strEntryFunction		- 入口函数
	 */
	void Start(const char* strStartLuaFile, const char* strEntryFunction);

	/**
	 * 导出Cpp到lua
	 */
	void BindCppToLua();

	/**
	 * 输出lua虚拟栈的内容
	 * In ->  bool bPrintTable					- 是否输出table表中的内容
	 */
	void DumpStack(bool bPrintTable = false);

private:
	/**
	 * 添加lua目录
	 */
	void AddSearchPath();
	/**
	 * 获取Lua Script目录
	 */
	bool GetScriptPath(char* strOutPath, size_t length);

	/**
	 * 输出lua虚拟栈中table的内容
	 * In ->  int index							- lua虚拟栈中的索引
	 */
	void PrintTable(int index);

private:
	lua_State* m_pLuaState;
};