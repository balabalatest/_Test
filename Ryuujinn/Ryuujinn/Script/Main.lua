require "Logger"

function Main()
	Logger.Log("Main")
	--将16进制字符串转换成10进制数字
	local flag = "00000020"
	flag = tonumber(flag, 16)

	Renderer.Init(flag)
	--这里需要设置lua查找路径
	gGame = require("Game")
	gGame.pSDLWindow = Renderer.CreateWindow("Test", 100, 100, 500, 500, 0)
	gGame.pSDLRenderer = Renderer.CreateRenderer(gGame.pSDLWindow, -1, 0)
	
	--while循环中添加print函数是为了避免执行太快，窗口一闪而过
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