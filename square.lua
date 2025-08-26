local s1 = square(200, 200, 100)
set_stroke(s1, "#ff0000", 10)

animate(s1, "rotate", {
	start=0,
	duration=5,
	timing="ease_in_out",
	loop="once",
	fromA=0,
	toA= 5 * math.pi
})
