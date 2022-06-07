function init()
	cAddCommand(".test", 50, "testCmd")
	cAddCommand("!town", 0, "teleportToTown")
end

function testCmd(playerHandle, argNum, ...)
	local args = {...}
	
	for i, v in ipairs(args) do
		cNoticeText(playerHandle, v)
	end
end

function teleportToTown(playerHandle, argNum, ...)
	local args = {...}
	
	cLinkTo(playerHandle, "RouN", 6884, 7200)
end

