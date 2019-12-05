require "Module.Enum.SDL"

local GameBase = 
{
	m_bIsRunning = false,	--是否在运行
	m_pSDLWindow = nil,		--SDL_Window指针
	m_pSDLRenderer = nil,	--SDL_Renderer指针

	m_title = "Game",		--窗口标题
	m_width = 0,			--窗口宽度
	m_height = 0,			--窗口高度
	m_bFullscreen = false,	--是否是全屏运行

	m_lastTime = 0,			--上次运行时间
}

--初始化
function GameBase:Init()
	self.m_bIsRunning = false

	--SDL初始化
	local flags = SDL_INIT_TYPE.SDL_INIT_VIDEO
	local bResult = Renderer.SDLInit(flags)
	if not bResult then
		Logger.LogError("Renderer.SDLInit(%d) failed, %s", flags, Renderer.GetError())
		return false
	end

	--读取Window.ini配置
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

	--根据Window.ini配置创建SDL窗口
	flags = 0
	if self.m_bFullscreen then
		flags = flags | SDL_WINDOW_TYPE.SDL_WINDOW_FULLSCREEN
	end
	self.m_pSDLWindow = Renderer.CreateWindow(self.m_title, 100, 100, self.m_width, self.m_height, flags)

	--创建SDLRenderer
	flags = SDL_RENDERER_TYPE.SDL_RENDERER_ACCELERATED | SDL_RENDERER_TYPE.SDL_RENDERER_PRESENTVSYNC
	self.m_pSDLRenderer = Renderer.CreateRenderer(self.m_pSDLWindow, -1, flags)

	--SDL_Image初始化
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

--运行
function GameBase:Run()
	while self:IsRunning() do
		self:HandleEvents()
		self:Update()
		self:Render()
	end
end

--释放
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

--是否在运行中
function GameBase:IsRunning()
	return self.m_bIsRunning
end

--退出游戏
function GameBase:QuitGame()
	self.m_bIsRunning = false
end

--事件处理
function GameBase:HandleEvents()
	local bResult, eventType = Renderer.PollEvent()
	while bResult do
		if eventType == SDL_EVENT_TYPE.SDL_QUIT then
			self:QuitGame()
		else--other event

		end

		bResult, eventType = Renderer.PollEvent()
	end

	--按下Escape键退出游戏
	bResult = Renderer.GetKeyboardState(SDL_KEYCODE.SDL_SCANCODE_ESCAPE)
	if bResult then
		self:QuitGame()
	end

	if self.OnHandleInput then
		self:OnHandleInput()
	end
end

--更新
function GameBase:Update()
	--限制一帧至少16ms
	while not Renderer.TICKS_PASSED(Renderer.GetTicks(), self.m_lastTime + 16) do
	end
	
	local currentTime = Renderer.GetTicks()
	local deltaTime = (currentTime - self.m_lastTime) / 1000
	self.m_lastTime = currentTime

	--调试会导致deltaTime变大，限制一下
	if deltaTime > 0.05 then
		deltaTime = 0.05
	end

	if self.OnUpdate then
		self:OnUpdate(deltaTime)
	end
end

--渲染
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