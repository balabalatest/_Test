#pragma once

class Logger
{
public:
	/**
	 * 在控制台上输出红色的信息
	 */
	static void LogError(const char* fmt, ...);
	/**
	 * 在控制台上输出黄色的信息
	 */
	static void LogWarning(const char* fmt, ...);
	/**
	 * 在控制台上输出白色的信息
	 */
	static void Log(const char* fmt, ...);

	/**
	 * 修改控制台上输出信息的颜色为红色
	 */
	static void SwtichColorToRed();
	/**
	 * 修改控制台上输出信息的颜色为黄色
	 */
	static void SwitchColorToYellow();
	/**
	 * 修改控制台上输出信息的颜色为白色
	 */
	static void SwitchColorToWhite();
};

struct lua_State;
namespace LuaWrap
{
	void RegisterLogger(lua_State* L);
}