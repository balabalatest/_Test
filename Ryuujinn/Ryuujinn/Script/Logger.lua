Logger.LogError = function(fmt, ...)
	Logger.SwtichColorToRed()
	print(string.format(fmt, ...))
	Logger.SwitchColorToWhite()
end

Logger.LogWarning = function(fmt, ...)
	Logger.SwitchColorToYellow()
	print(string.format(fmt, ...))
	Logger.SwitchColorToWhite()
end

Logger.Log = function(fmt, ...)
	print(string.format(fmt, ...))
end