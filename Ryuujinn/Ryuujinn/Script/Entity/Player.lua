local Player = {}
Player.__index = Player
setmetatable(Player, require "Entity.Actor")

function Player:OnInit()
	local spriteComponent = require("Module.Component.SpriteComponent"):New(self)
	if self:GetGame() then
		local textureName = "Resource/img/char/body.png"
		spriteComponent:SetTexture(TextureManager:GetTexture(self:GetGame():GetRenderer(), textureName))
	end
	self:SetPosition(170, 360)
	self:SetScale(100, 100)
end

function Player:HandleInput()
	local x, y = self:GetPosition()
	if Renderer.GetKeyboardState(SDL_KEYCODE.SDL_SCANCODE_W) then
		y = y - 10
	end
	if Renderer.GetKeyboardState(SDL_KEYCODE.SDL_SCANCODE_S) then
		y = y + 10
	end
	if Renderer.GetKeyboardState(SDL_KEYCODE.SDL_SCANCODE_A) then
		x = x - 10
	end
	if Renderer.GetKeyboardState(SDL_KEYCODE.SDL_SCANCODE_D) then
		x = x + 10
	end
	self:SetPosition(x, y)
end

function Player:OnUpdate()
	
end

function Player:OnRelease()
end

return Player