#pragma once

class Texture
{
public:
	Texture();
	Texture(struct SDL_Renderer* pRenderer, const char* fileName);
	virtual ~Texture();

	/**
	 * ��Ⱦ��ͼ
	 * In ->  struct SDL_Renderer* pRenderer		
	 *		  int x, int y						- ��ʾλ��
	 */
	void Render(struct SDL_Renderer* pRenderer, int x, int y);
	/**
	 * ��Ⱦ��ͼ
	 * In ->  struct SDL_Renderer* pRenderer
	 *		  int x, int y						- ��ʾλ��
	 *		  int width, int height				- ��ʾ�Ŀ�ߣ�����ͨ����2��ֵ�������ţ�
	 */
	void Render(struct SDL_Renderer* pRenderer, int x, int y, int width, int height);

private:
	/**
	 * ��ȡ��ͼ�������
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