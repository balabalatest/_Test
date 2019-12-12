TextureManager = 
{
	m_textures = {},	--����C++Texture����
}

--��ȡTexture��û�оͼ��ص��ڴ���
function TextureManager:GetTexture(pRenderer, textureName)
	--Logger.Log("pRenderer: "..tostring(pRenderer))
	--Logger.Log("textureName: "..tostring(textureName))
	--û�оͼ��ص��ڴ��У���������ô���Ϊ1
	if nil == self.m_textures[textureName] then
		self.m_textures[textureName] = {}
		self.m_textures[textureName].pTexture = Texture.New(pRenderer, textureName)
		self.m_textures[textureName].count = 1
	else
		--������ô�������1
		self.m_textures[textureName].count = self.m_textures[textureName].count + 1
	end

	return self.m_textures[textureName].pTexture
end

function TextureManager:RemoveTexture(pTexture)
	if nil == pTexture then return end
	--���ң����������ô���1�Σ�������ô���С��0�����ͷ��ڴ�
	for k, v in pairs(self.m_textures) do
		if v.pTexture == pTexture then
			self.m_textures[k].count = self.m_textures[k].count - 1
			if self.m_textures[k].count <= 0 then
				self.m_textures[k] = nil
				break
			end
		end
	end
end