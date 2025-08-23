#include "canim.h"

t_animate *create_animation(t_animtype type, double start, double duration, double timing, t_animrepeat repeat) {
	t_animate *animation = malloc(sizeof(t_animate));
	if (!animation)
		return NULL;
	animation->type = type;
	animation->start = start;
	animation->duration = duration;
	animation->timing = timing;
	animation->repeat = repeat;
	animation->next = NULL;
	return animation;
}

t_animate *add_animation(t_animate *head, t_animate *new) {
	t_animate *mem = head;
	if (!head)
		return new;
	while (head->next)
		head = head->next;
	head->next = new;
	return mem;
}
