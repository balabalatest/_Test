#pragma once

class Logger
{
public:
	/**
	 * �ڿ���̨�������ɫ����Ϣ
	 */
	static void LogError(const char* fmt, ...);
	/**
	 * �ڿ���̨�������ɫ����Ϣ
	 */
	static void LogWarning(const char* fmt, ...);
	/**
	 * �ڿ���̨�������ɫ����Ϣ
	 */
	static void Log(const char* fmt, ...);

	/**
	 * �޸Ŀ���̨�������Ϣ����ɫΪ��ɫ
	 */
	static void SwtichColorToRed();
	/**
	 * �޸Ŀ���̨�������Ϣ����ɫΪ��ɫ
	 */
	static void SwitchColorToYellow();
	/**
	 * �޸Ŀ���̨�������Ϣ����ɫΪ��ɫ
	 */
	static void SwitchColorToWhite();
};

struct lua_State;
namespace LuaWrap
{
	void RegisterLogger(lua_State* L);
}