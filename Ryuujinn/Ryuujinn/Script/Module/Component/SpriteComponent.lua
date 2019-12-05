local SpriteComponent = 
{
	m_pTexture = nil,			--C++ Texture¿‡
	m_renderOrder = 100,		--‰÷»æÀ≥–Ú
}
SpriteComponent.__index = SpriteComponent
setmetatable(SpriteComponent, require "Module.Component.Component")

function SpriteComponent:OnInit(renderOrder)
	self.m_renderOrder = renderOrder
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
end

return SpriteComponent