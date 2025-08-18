# CANIM

## Do you know Manim (the math animation lib in python) ?
## Here come canim (first goal is to dipaly svgs and morph them)

## Quadratic Bézier

Let the control points be:

$$p = (x_1, y_1), \quad q = (x_2, y_2), \quad s = (x_3, y_3)$$

We define:

$$a(t) = q + (1 - t)(p - q), \quad 0 \leq t \leq 1$$

$$b(t) = q + t(s - q), \quad 0 \leq t \leq 1$$

Then the quadratic Bézier curve is:

$$B(t) = a(t) + t \big(b(t) - a(t)\big), \quad 0 \leq t \leq 1$$

---

## Cubic Bézier

Let the control points be:

$$p_1 = (c_1, v_1), \quad p_2 = (c_2, v_2), \quad p_3 = (c_3, v_3), \quad p_4 = (c_4, v_4)$$

The parametric form is:

$$B_x(t) = (1 - t)^3 c_1 + 3t(1 - t)^2 c_2 + 3t^2 (1 - t) c_3 + t^3 c_4$$

$$B_y(t) = (1 - t)^3 v_1 + 3t(1 - t)^2 v_2 + 3t^2 (1 - t) v_3 + t^3 v_4$$

So the cubic Bézier curve is:

$$B(t) = \big( B_x(t), \, B_y(t) \big), \quad 0 \leq t \leq 1$$

