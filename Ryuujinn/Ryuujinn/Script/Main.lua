require "Logger"

function Main()
	Logger.Log("Main")
	--��16�����ַ���ת����10��������
	local flag = "00000020"
	flag = tonumber(flag, 16)

	Renderer.Init(flag)
	--������Ҫ����lua����·��
	gGame = require("Game")
	gGame.pSDLWindow = Renderer.CreateWindow("Test", 100, 100, 500, 500, 0)
	gGame.pSDLRenderer = Renderer.CreateRenderer(gGame.pSDLWindow, -1, 0)
	
	--whileѭ�������print������Ϊ�˱���ִ��̫�죬����һ������
	local count = 1
	while count < 10000 do
		count = count + 1
		--Logger.LogError(count)
	end
	
	Renderer.DestroyRenderer(gGame.pSDLRenderer)
	Renderer.DestroyWindow(gGame.pSDLWindow)
	Renderer.Quit()

	Logger.LogError("%s is %d, have %f", "jack", 18, 990.0011)
	Logger.LogWarning("%s is %d, have %f", "jack", 18, 990.0011)
	Logger.Log("%s is %d, have %f", "jack", 18, 990.0011)
end