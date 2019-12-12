local SpriteComponent = 
{
	m_pTexture = nil,			--C++ Texture类
	m_renderOrder = 100,		--渲染顺序
}
SpriteComponent.__index = SpriteComponent
setmetatable(SpriteComponent, require "Module.Component.Component")

function SpriteComponent:OnInit(renderOrder)
	self.m_renderOrder = renderOrder
	--将该组件对象传入到RyuujinnGame中的m_pSpriteComponents列表中
	--由RyuujinnGame来管理该组件的渲染等
	--因此RyuujinnGame可以根据渲染顺序（m_renderOrder）来控制那个先渲染
	if self:GetActor() and self:GetActor():GetGame() then
		self:GetActor():GetGame():AddSpriteComponent(self)
	end
end

function SpriteComponent:GetRenderOrder()
	return self.m_renderOrder
end

function SpriteComponent:Render(pSDLRenderer)
	if nil == pSDLRenderer or nil == self.m_pTexture then return end

	local pActor = self:GetActor()
	if nil == pActor then return end

	--获取Actor的位置和缩放来渲染图片
	local x, y = pActor:GetPosition()
	local width, height = pActor:GetScale()
	if (1 == width and 1 == height) or (nil == width and nil == height) then
		self.m_pTexture:Render(pSDLRenderer, x, y)
	else
		self.m_pTexture:Render(pSDLRenderer, x, y, width, height)
	end
end

function SpriteComponent:SetTexture(pTexture)
	self.m_pTexture = pTexture
end

function SpriteComponent:OnRelease()
	if self:GetActor() and self:GetActor():GetGame() then
		self:GetActor():GetGame():RemoveSpriteComponent(self)
	end
	TextureManager:RemoveTexture(self.m_pTexture)
	self.m_pTexture = nil
end

return SpriteComponent