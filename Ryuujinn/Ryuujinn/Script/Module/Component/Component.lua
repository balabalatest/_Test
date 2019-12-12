local Component = 
{
	m_pActor = nil,			--拥有者
	m_updateOrder = 100,	--更新顺序
}
Component.__index = Component

--构造函数
function Component:New(pActor, updateOrder, ...)
	local newTable = {}
	setmetatable(newTable, self)
	self.__index = self
	newTable.m_pActor = pActor
	newTable.m_updateOrder = updateOrder
	--将该组件对象传入到Actor中的m_components列表中
	--由Actor来管理该组件对象的更新释放等
	--因此Actor可以根据更新顺序（m_updateOrder）来控制那个组件先更新
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

--子类通过实现OnUpdate来完成多态
function Component:Update(deltaTime)
	if self.OnUpdate then
		self:OnUpdate(deltaTime)
	end
end

--相当于析构函数，将该组件对象从Acotr中的m_components列表中移除
--子类通过实现OnRelease来完成多态，
function Component:Release()
	if self:GetActor() then
		self:GetActor():RemoveComponent(newTable)
	end
	if self.OnRelease then
		self:OnRelease()
	end
end

return Component