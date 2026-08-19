local W = 1280
local H = 720
local CX = W / 2
local CY = H / 2
local PI = math.pi
local TAU = 2 * PI

local function add_create(shape, duration, timing)
	animate(shape, "create", {
		start = 0,
		duration = duration,
		timing = timing or "ease_in_out",
		loop = "infinite",
	})
end

local function add_rotate(shape, duration, from_a, to_a, timing)
	animate(shape, "rotate", {
		start = 0,
		duration = duration,
		timing = timing or "ease_in_out",
		loop = "infinite",
		fromA = from_a or 0,
		toA = to_a or TAU,
	})
end

local function add_translate(shape, duration, from_x, from_y, to_x, to_y, timing)
	animate(shape, "translate", {
		start = 0,
		duration = duration,
		timing = timing or "linear",
		loop = "infinite",
		from = { from_x or 0, from_y or 0 },
		to = { to_x or 0, to_y or 0 },
	})
end

local function orbiting_circle(x, y, r, stroke, width, opacity, duration, steps)
	local c = circle(x, y, r)
	set_stroke(c, stroke, width, opacity)
	add_create(c, 1.4, "ease_out")

	for i = 1, #steps do
		local step = steps[i]
		add_translate(c, duration / #steps, 0, 0, step[1], step[2], "ease_in_out")
	end

	return c
end

local function rotating_square(x, y, size, angle, stroke, width, opacity, duration)
	local s = square(x, y, size, angle or 0)
	set_stroke(s, stroke, width, opacity)
	add_create(s, 1.1, "ease_out")
	add_rotate(s, duration, 0, TAU, "ease_in_out")
	return s
end

local function ring(x, y, r, stroke, width, opacity, duration)
	local c = circle(x, y, r)
	set_stroke(c, stroke, width, opacity)
	add_create(c, duration, "ease_in_out")
	add_rotate(c, 16, 0, -TAU, "linear")
	return c
end

-- Soft architectural frame
ring(CX, CY, 290, "#ffb14a", 4, 90, 2.2)
ring(CX, CY, 220, "#ff8a1f", 3, 60, 2.0)
ring(CX, CY, 150, "#ff6a00", 3, 50, 1.8)

-- Central mark
rotating_square(CX, CY, 170, 0, "#fff1dc", 7, 230, 16)
rotating_square(CX, CY, 92, 0, "#ffb14a", 6, 220, 10)
rotating_square(CX, CY, 38, 0, "#ff8a1f", 5, 230, 12)

-- Four orbiting nodes
orbiting_circle(
	CX + 190,
	CY,
	24,
	"#ffb14a",
	6,
	220,
	12,
	{
		{ 0, -110 },
		{ -110, 0 },
		{ 0, 110 },
		{ 110, 0 },
	}
)

orbiting_circle(
	CX,
	CY - 190,
	20,
	"#ff8a1f",
	6,
	220,
	12,
	{
		{ -110, 0 },
		{ 0, 110 },
		{ 110, 0 },
		{ 0, -110 },
	}
)

orbiting_circle(
	CX - 190,
	CY,
	24,
	"#ff6a00",
	6,
	220,
	12,
	{
		{ 0, 110 },
		{ 110, 0 },
		{ 0, -110 },
		{ -110, 0 },
	}
)

orbiting_circle(
	CX,
	CY + 190,
	20,
	"#ffe0b8",
	5,
	200,
	12,
	{
		{ 110, 0 },
		{ 0, -110 },
		{ -110, 0 },
		{ 0, 110 },
	}
)

-- Corner accents, slower and more restrained.
rotating_square(CX - 330, CY - 180, 36, 0, "#ffb14a", 3, 120, 18)
rotating_square(CX + 330, CY - 180, 36, 0, "#ff8a1f", 3, 120, 18)
rotating_square(CX - 330, CY + 180, 36, 0, "#ff6a00", 3, 120, 18)
rotating_square(CX + 330, CY + 180, 36, 0, "#ffe0b8", 3, 120, 18)
