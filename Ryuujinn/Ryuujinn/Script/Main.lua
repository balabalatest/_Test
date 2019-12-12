require "Logger"

require "RyuujinnGame"

function Main()
	Logger.Log("Main")

	local bResult = RyuujinnGame:Init()
	if bResult then
		RyuujinnGame:Run()
	end
	
	RyuujinnGame:Release()
end