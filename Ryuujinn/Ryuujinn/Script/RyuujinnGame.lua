require "Module.Enum.ActorState"
require "Manager.TextureManager"

RyuujinnGame = 
{
	m_bUpdatingActors = true,		--���ڸ���Actors
	m_pActors = {},					--���ڻ�е�Actors
	m_pPendingActors = {},			--�´�����Actors
	m_pSpriteComponents = {},		--��ȾSprite
	m_pPlayer = nil,				--����
}
setmetatable(RyuujinnGame, 
{ 
	__index = require "GameBase",
	__newindex = function(t, key, newValue)--��ֹ����GameBase����
		local oldValue = t[key]
		if oldValue == nil or type(oldValue) ~= "function" then
			rawset(t, key, newValue)
		else
			Logger.LogError("This action overrides GameBase's function is not allowed\n"..debug.traceback())
		end
	end
})

function RyuujinnGame:OnInit()
	--��ӱ���
	require("Entity.BG"):New(self, "Resource/img/board/10.png", 0, 0)
	require("Entity.BG"):New(self, "Resource/img/board/11.png", 0, 16)
	require("Entity.BG"):New(self, "Resource/img/board/12.png", 0, 464)
	require("Entity.BG"):New(self, "Resource/img/board/20.png", 416, 0)
	--������
	self.m_pPlayer = require("Entity.Player"):New(self)
	return true
end

function RyuujinnGame:OnRelease()
	for i = #self.m_pActors, 1, -1 do
		self.m_pActors[i]:Release()
	end
	for i = #self.m_pPendingActors, 1, -1 do
		self.m_pPendingActors[i]:Release()
	end
end

function RyuujinnGame:OnHandleInput()
	if self.m_pPlayer and self.m_pPlayer.HandleInput then
		self.m_pPlayer:HandleInput()
	end

	--�����Ƿ��е���GC���ͷ�C++ Texture��Դ
	if Renderer.GetKeyboardState(SDL_KEYCODE.SDL_SCANCODE_F) then
		if self.m_pPlayer then
			self.m_pPlayer:Release()
			self.m_pPlayer = nil
		end
	end
end

function RyuujinnGame:OnUpdate(deltaTime)
	collectgarbage("collect")
	self:UpdateActor(deltaTime)
end

function RyuujinnGame:OnRender()
	self:RenderSpriteComponent()
end

function RyuujinnGame:AddActor(pActor)
	if self.m_bUpdatingActors then
		table.insert(self.m_pPendingActors, pActor)
	else
		table.insert(self.m_pActors, pActor)
	end
end

function RyuujinnGame:RemoveActor(pActor)
	for i = #self.m_pPendingActors, 1, -1 do
		if self.m_pPendingActors[i] == pActor then
			table.remove(self.m_pPendingActors, i)
		end
	end

	for i = #self.m_pActors, 1, -1 do
		if self.m_pActors[i] == pActor then
			table.remove(self.m_pActors, i)
		end
	end
end

function RyuujinnGame:UpdateActor(deltaTime)
	self.m_bUpdatingActors = true
	for k, v in pairs(self.m_pActors) do
		v:Update(deltaTime)
	end
	self.m_bUpdatingActors = false

	for i = #self.m_pPendingActors, 1, -1 do
		table.insert(self.m_pActors, self.m_pPendingActors[i])
		table.remove(self.m_pPendingActors, i)
	end

	local deadActors = {}
	for i = #self.m_pActors, 1, -1 do
		if self.m_pActors[i]:IsDead() then
			table.insert(deadActors, self.m_pActors[i])
		end
	end

	for i = #deadActors, 1, -1 do
		deadActors[i]:Release()
	end
end

--������������򣬸�����Ⱦ˳��
local function SortSpriteComponent(a, b)
	if a:GetRenderOrder() ~= b:GetRenderOrder() then
		return a:GetRenderOrder() < b:GetRenderOrder()
	end
	return false
end

function RyuujinnGame:AddSpriteComponent(pSpriteComponent)
	table.insert(self.m_pSpriteComponents, pSpriteComponent)
	table.sort(self.m_pSpriteComponents, SortSpriteComponent)
end

function RyuujinnGame:RemoveSpriteComponent(pSpriteComponent)
	for i = #self.m_pSpriteComponents, 1, -1 do
		if self.m_pSpriteComponents[i] == pSpriteComponent then
			table.remove(self.m_pSpriteComponents, i)
		end
	end
end

function RyuujinnGame:RenderSpriteComponent()
	for i = 1, #self.m_pSpriteComponents do
		self.m_pSpriteComponents[i]:Render(self:GetRenderer())
	end
end