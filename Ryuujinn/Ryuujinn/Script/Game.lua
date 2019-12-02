local GameBase = 
{
	pSDLWindow = nil,
	pSDLRenderer = nil
}

local Game = setmetatable({}, { __index = GameBase })

return Game