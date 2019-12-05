require "Module.Enum.SDL"

local GameBase = 
{
	m_bIsRunning = false,	--�Ƿ�������
	m_pSDLWindow = nil,		--SDL_Windowָ��
	m_pSDLRenderer = nil,	--SDL_Rendererָ��

	m_title = "Game",		--���ڱ���
	m_width = 0,			--���ڿ��
	m_height = 0,			--���ڸ߶�
	m_bFullscreen = false,	--�Ƿ���ȫ������

	m_lastTime = 0,			--�ϴ�����ʱ��
}

--��ʼ��
function GameBase:Init()
	self.m_bIsRunning = false

	--SDL��ʼ��
	local flags = SDL_INIT_TYPE.SDL_INIT_VIDEO
	local bResult = Renderer.SDLInit(flags)
	if not bResult then
		Logger.LogError("Renderer.SDLInit(%d) failed, %s", flags, Renderer.GetError())
		return false
	end

	--��ȡWindow.ini����
	local filePath = "Config/Window.ini"
	local windowConfig = io.open(filePath, "r")
	if not windowConfig then
		Logger.LogError("Error: Can't find %s", filePath)
		return false
	end
	self.m_title = windowConfig:read()
	self.m_width = tonumber(windowConfig:read())
	self.m_height = tonumber(windowConfig:read())
	self.m_bFullscreen = tonumber(windowConfig:read()) ~= 0
	windowConfig:close()

	--����Window.ini���ô���SDL����
	flags = 0
	if self.m_bFullscreen then
		flags = flags | SDL_WINDOW_TYPE.SDL_WINDOW_FULLSCREEN
	end
	self.m_pSDLWindow = Renderer.CreateWindow(self.m_title, 100, 100, self.m_width, self.m_height, flags)

	--����SDLRenderer
	flags = SDL_RENDERER_TYPE.SDL_RENDERER_ACCELERATED | SDL_RENDERER_TYPE.SDL_RENDERER_PRESENTVSYNC
	self.m_pSDLRenderer = Renderer.CreateRenderer(self.m_pSDLWindow, -1, flags)

	--SDL_Image��ʼ��
	flags = SDL_IMAGE_INIT_TYPE.IMG_INIT_PNG
	bResult = Renderer.SDLImageInit(flags)
	if not bResult then
		Logger.LogError("Renderer.SDLImageInit(%d) failed, %s", flags, Renderer.GetError())
		return false
	end

	if self.OnInit then
		bResult = self:OnInit()
		if not bResult then
			return false
		end
	end

	self.m_bIsRunning = true

	return true
end

--����
function GameBase:Run()
	while self:IsRunning() do
		self:HandleEvents()
		self:Update()
		self:Render()
	end
end

--�ͷ�
function GameBase:Release()
	if self.OnRelease then
		self:OnRelease()
	end

	if self.m_pSDLRenderer then
		Renderer.DestroyRenderer(self.m_pSDLRenderer)
	end
	if self.m_pSDLWindow then
		Renderer.DestroyWindow(self.m_pSDLWindow)
	end
	Renderer.Quit()
end

--�Ƿ���������
function GameBase:IsRunning()
	return self.m_bIsRunning
end

--�˳���Ϸ
function GameBase:QuitGame()
	self.m_bIsRunning = false
end

--�¼�����
function GameBase:HandleEvents()
	local bResult, eventType = Renderer.PollEvent()
	while bResult do
		if eventType == SDL_EVENT_TYPE.SDL_QUIT then
			self:QuitGame()
		else--other event

		end

		bResult, eventType = Renderer.PollEvent()
	end

	--����Escape���˳���Ϸ
	bResult = Renderer.GetKeyboardState(SDL_KEYCODE.SDL_SCANCODE_ESCAPE)
	if bResult then
		self:QuitGame()
	end

	if self.OnHandleInput then
		self:OnHandleInput()
	end
end

--����
function GameBase:Update()
	--����һ֡����16ms
	while not Renderer.TICKS_PASSED(Renderer.GetTicks(), self.m_lastTime + 16) do
	end
	
	local currentTime = Renderer.GetTicks()
	local deltaTime = (currentTime - self.m_lastTime) / 1000
	self.m_lastTime = currentTime

	--���Իᵼ��deltaTime�������һ��
	if deltaTime > 0.05 then
		deltaTime = 0.05
	end

	if self.OnUpdate then
		self:OnUpdate(deltaTime)
	end
end

--��Ⱦ
function GameBase:Render()
	Renderer.SetRenderDrawColor(self.m_pSDLRenderer, 0, 0, 255, 255)
	Renderer.RenderClear(self.m_pSDLRenderer)

	if self.OnRender then
		self:OnRender()
	end

	Renderer.RenderPresent(self.m_pSDLRenderer)
end

function GameBase:GetRenderer()
	return self.m_pSDLRenderer
end

return GameBase