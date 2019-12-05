local BG = {}
BG.__index = BG
setmetatable(BG, require "Entity.Actor")

function BG:OnInit(textureName, x, y)
	local spriteComponent = require("Module.Component.SpriteComponent"):New(self)
	if self:GetGame() then
		spriteComponent:SetTexture(TextureManager:GetTexture(self:GetGame():GetRenderer(), textureName))
	end
	self:SetPosition(x, y)
end

function BG:OnUpdate()
end

function BG:OnRelease()
end

return BG