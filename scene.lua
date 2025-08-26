local c3 = circle(640, 360, 100)
set_stroke(c3, "#aaaa", 10)

animate(c3, "create", {
    start=0,
    duration=0.1,
    timing="linear",
    loop="infinite"
})

animate(c3, "translate", {
    start=10,
    duration=2,
    timing="linear",
    loop="infinite",
	from={0, 0},
	to={200, 200}
})

animate(c3, "translate", {
    start=16,
    duration=2,
    timing="linear",
    loop="infinite",
	from={0, 0},
	to={-200, -200}
})
