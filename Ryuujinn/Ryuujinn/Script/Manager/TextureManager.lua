TextureManager = 
{
	m_pTextures = {},	--����C++Texture����
}

--��ȡTexture��û�оͼ��ص��ڴ���
function TextureManager:GetTexture(pRenderer, textureName)
	--Logger.Log("pRenderer: "..tostring(pRenderer))
	--Logger.Log("textureName: "..tostring(textureName))
	if nil == self.m_pTextures[textureName] then
		self.m_pTextures[textureName] = Texture.New(pRenderer, textureName)
	end

	return self.m_pTextures[textureName]
end

function TextureManager:RemoveTexture(pTexture)
	for k, v in pairs(self.m_pTextures) do
		if v == pTexture then
			self.m_pTextures[textureName] = nil
		end
	end
end