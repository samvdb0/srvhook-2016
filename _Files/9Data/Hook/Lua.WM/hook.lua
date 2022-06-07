function init()
	cAddTimer(240, "PlayerCountNotice")
end

function PlayerCountNotice()
	cNotice("There are currently " .. cSessionCount() .. " people playing!")
end