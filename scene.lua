local width = 1280
local height = 720
local r = 50
local offset = 20
local ms_mod = 4

-- 🌸 square path moves (right, down, left, up)
local square_moves = {
	{ width - 2 * r - 2 * offset, 0 },
	{ 0, height - 2 * r - 2 * offset },
	{ -(width - 2 * r - 2 * offset), 0 },
	{ 0, -(height - 2 * r - 2 * offset) },
}

-- 🌸 square starting positions (corners)
local corners = {
	{ offset + r, offset + r }, -- top-left
	{ width - r - offset, offset + r }, -- top-right
	{ width - r - offset, height - r - offset }, -- bottom-right
	{ offset + r, height - r - offset }, -- bottom-left
}

-- 🌸 corner grey circles
for n = 1, 4 do
	local c = circle(corners[n][1], corners[n][2], r)
	set_stroke(c, "#aaaa", 10)

	animate(c, "create", { start = 0, duration = 1, timing = "linear", loop = "infinite" })

	for i = 1, #square_moves do
		local move = square_moves[((i + n - 2) % #square_moves) + 1]
		animate(c, "translate", {
			start = 0,
			duration = 1 / ms_mod,
			timing = "linear",
			loop = "infinite",
			from = { 0, 0 },
			to = move,
		})
	end
end

-- ❤️ red ones (center → up/left/down/right → back to center)
local center = { width / 2, height / 2 }
local cross_moves = {
	{ 0, -(height / 2 - r - offset) }, -- up
	{ -(width / 2 - r - offset), 0 }, -- left
	{ 0, (height / 2 - r - offset) }, -- down
	{ (width / 2 - r - offset), 0 }, -- right
}

for n = 1, 4 do
	local c = circle(center[1], center[2], r)
	set_stroke(c, "#ff0000", 10) -- red ❤️

	animate(c, "create", { start = 0, duration = 1, timing = "linear", loop = "infinite" })

	animate(c, "translate", {
		start = 0,
		duration = 2 / ms_mod,
		timing = "linear",
		loop = "infinite",
		from = { 0, 0 },
		to = cross_moves[n],
	})
	animate(c, "translate", {
		start = 0,
		duration = 2 / ms_mod,
		timing = "linear",
		loop = "infinite",
		from = { 0, 0 },
		to = { -cross_moves[n][1], -cross_moves[n][2] },
	})
end

-- 💚 green ones (losange around screen: top → left → bottom → right → top)
local diamond_points = {
	{ width / 2, 0 }, -- top
	{ 0, height / 2 }, -- left
	{ width / 2, height }, -- bottom
	{ width, height / 2 }, -- right
}

local diamond_moves = {
	{ -(width / 2), height / 2 }, -- top → left
	{ width / 2, height / 2 }, -- left → bottom
	{ width / 2, -(height / 2) }, -- bottom → right
	{ -(width / 2), -(height / 2) }, -- right → top
}

for n = 1, 4 do
	local start = diamond_points[n]
	local c = circle(start[1], start[2], r)
	set_stroke(c, "#00ff00", 10) -- green 💚

	animate(c, "create", { start = 0, duration = 1, timing = "linear", loop = "infinite" })

	for i = 1, #diamond_moves do
		local move = diamond_moves[((i + n - 2) % #diamond_moves) + 1]
		animate(c, "translate", {
			start = 1,
			duration = 2 / ms_mod,
			timing = "linear",
			loop = "infinite",
			from = { 0, 0 },
			to = move,
		})
	end
end
