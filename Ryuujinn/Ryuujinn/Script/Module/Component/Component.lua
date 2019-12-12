local Component = 
{
	m_pActor = nil,			--ӵ����
	m_updateOrder = 100,	--����˳��
}
Component.__index = Component

--���캯��
function Component:New(pActor, updateOrder, ...)
	local newTable = {}
	setmetatable(newTable, self)
	self.__index = self
	newTable.m_pActor = pActor
	newTable.m_updateOrder = updateOrder
	--������������뵽Actor�е�m_components�б���
	--��Actor��������������ĸ����ͷŵ�
	--���Actor���Ը��ݸ���˳��m_updateOrder���������Ǹ�����ȸ���
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

--����ͨ��ʵ��OnUpdate����ɶ�̬
function Component:Update(deltaTime)
	if self.OnUpdate then
		self:OnUpdate(deltaTime)
	end
end

--�൱������������������������Acotr�е�m_components�б����Ƴ�
--����ͨ��ʵ��OnRelease����ɶ�̬��
function Component:Release()
	if self:GetActor() then
		self:GetActor():RemoveComponent(newTable)
	end
	if self.OnRelease then
		self:OnRelease()
	end
end

return Component