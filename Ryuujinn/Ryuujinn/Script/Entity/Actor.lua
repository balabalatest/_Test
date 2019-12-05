local Actor = 
{
	m_game = nil,								--游戏类
	m_actorState = ActorState.Active,			--状态
	--m_position = { x = 0.0, y = 0.0 },		--位置
	--m_scale = { width = 1.0, height = 1.0 },	--缩放
	--m_components = {},						--所有组件
}
Actor.__index = Actor

function Actor:New(game, ...)
	local newTable = 
	{
		m_position = { x = 0.0, y = 0.0 },			
		m_scale = { width = 1.0, height = 1.0 },	
		m_components = {}
	}
	setmetatable(newTable, self)
	self.__index = self
	newTable.m_game = game
	if newTable:GetGame() then
		newTable:GetGame():AddActor(newTable)
	end
	if newTable.OnInit then
		newTable:OnInit(...)
	end
	return newTable
end

function Actor:IsDead()
	return ActorState.Dead == self.m_actorState
end

function Actor:GetGame()
	return self.m_game
end

function Actor:GetActorState()
	return self.m_actorState
end

function Actor:GetPosition()
	return self.m_position.x, self.m_position.y
end

function Actor:GetScale()
	return self.m_scale.width, self.m_scale.height
end

function Actor:SetActorState(actorState)
	self.m_actorState = actorState
end

function Actor:SetPosition(x, y)
	self.m_position.x, self.m_position.y = x, y
end

function Actor:SetScale(width, height)
	self.m_scale.width, self.m_scale.height = width, height
end

--对组件进行排序，根据更新顺序
local function SortComponent(a, b)
	if a:GetUpdateOrder() ~= b:GetUpdateOrder() then
		return a:GetUpdateOrder() < b:GetUpdateOrder()
	end
	return false
end

function Actor:AddComponent(pComponent)
	if nil == pComponent then return end

	table.insert(self.m_components, pComponent)
	table.sort(self.m_components, SortComponent)
end

function Actor:RemoveComponent(pComponent)
	if nil == pComponent then return end

	for i = #self.m_components, 1, -1 do
		if self.m_components[i] == pComponent then
			table.remove(self.m_components, i)
			return
		end
	end
end

function Actor:UpdateComponent(deltaTime)
	for i = 1, #self.m_components do
		if self.m_components[i] ~= nil then
			self.m_components[i]:Update(deltaTime)
		end
	end
end

function Actor:Update(deltaTime)
	if ActorState.Active == self.m_actorState then
		self:UpdateComponent()
		if self.OnUpdate then
			self:OnUpdate(deltaTime)
		end
	end
end

function Actor:Release()
	if self:GetGame() then
		self:GetGame():RemoveActor(self)
	end
	for i = #self.m_components, 1, -1 do
		self.m_components[i]:Release()
	end
	if self.OnRelease then
		self:OnRelease()
	end
end

return Actor