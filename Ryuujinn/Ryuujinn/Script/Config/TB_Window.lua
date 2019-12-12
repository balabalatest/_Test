local Window = 
{
	["1"] = 
	{
		title = "Ryuujinn",
		x = SDL_POSITION_TYPE.SDL_WINDOWPOS_CENTERED,
		y = SDL_POSITION_TYPE.SDL_WINDOWPOS_CENTERED,
		width = 640,
		height = 480,
		fullscreen = 0,
	},
}

do
	for k, v in pairs(Window) do
		local proxy = {}
		local mt = 
		{
			__index = v,
			__newindex = function(t, k, v)
				error("attempt to update a read-only talbe", 2)
			end
		}
		Window[k] = setmetatable(proxy, mt)
	end
end

return Window