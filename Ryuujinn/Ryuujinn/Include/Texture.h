#pragma once

class Texture
{
public:
	Texture();
	Texture(struct SDL_Renderer* pRenderer, const char* fileName);
	virtual ~Texture();

	/**
	 * 渲染贴图
	 * In ->  struct SDL_Renderer* pRenderer		
	 *		  int x, int y						- 显示位置
	 */
	void Render(struct SDL_Renderer* pRenderer, int x, int y);
	/**
	 * 渲染贴图
	 * In ->  struct SDL_Renderer* pRenderer
	 *		  int x, int y						- 显示位置
	 *		  int width, int height				- 显示的宽高（可以通过这2个值进行缩放）
	 */
	void Render(struct SDL_Renderer* pRenderer, int x, int y, int width, int height);

private:
	/**
	 * 获取贴图宽高数据
	 */
	void QueryTexture();

private:
	struct SDL_Texture* m_pSDLTexture = nullptr;
	int m_textureWidth = 0;
	int m_textureHeight = 0;
};

struct lua_State;
namespace LuaWrap
{
	void RegisterTexture(lua_State* L);
}