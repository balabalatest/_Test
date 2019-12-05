local Component = 
{
	m_pActor = nil,			--拥有者
	m_updateOrder = 100,	--更新顺序
}
Component.__index = Component

function Component:New(pActor, updateOrder, ...)
	local newTable = {}
	setmetatable(newTable, self)
	self.__index = self
	newTable.m_pActor = pActor
	newTable.m_updateOrder = updateOrder
	if newTable:GetActor() then
		newTable:GetActor():AddComponent(newTable)
	end
	if newTable.OnInit then
		newTable:OnInit(...)
	end
	return newTable
end

function Component:GetActor()
	return self.m_pActor
end

function Component:GetUpdateOrder()
	return self.m_updateOrder
end

function Component:Update(deltaTime)
	if self.OnUpdate then
		self:OnUpdate(deltaTime)
	end
end

function Component:Release()
	if self:GetActor() then
		self:GetActor():RemoveComponent(newTable)
	end
	if self.OnRelease then
		self:OnRelease()
	end
end

return Component