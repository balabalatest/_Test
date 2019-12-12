TextureManager = 
{
	m_textures = {},	--所有C++Texture对象
}

--获取Texture，没有就加载到内存中
function TextureManager:GetTexture(pRenderer, textureName)
	--Logger.Log("pRenderer: "..tostring(pRenderer))
	--Logger.Log("textureName: "..tostring(textureName))
	--没有就加载到内存中，并标记引用次数为1
	if nil == self.m_textures[textureName] then
		self.m_textures[textureName] = {}
		self.m_textures[textureName].pTexture = Texture.New(pRenderer, textureName)
		self.m_textures[textureName].count = 1
	else
		--标记引用次数自增1
		self.m_textures[textureName].count = self.m_textures[textureName].count + 1
	end

	return self.m_textures[textureName].pTexture
end

function TextureManager:RemoveTexture(pTexture)
	if nil == pTexture then return end
	--查找，并减少引用次数1次，如果引用次数小于0，就释放内存
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