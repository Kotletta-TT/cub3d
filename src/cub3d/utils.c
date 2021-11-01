#include "render.h"

double	to_degrees(double radians)
{
	return (radians * 180 / M_PI);
}

double	to_radians(double degree)
{
	return (degree * (M_PI / 180));
}

int is_facing_up(int angle, t_angle *a)
{
	return (angle > 0 && angle < a->a180);
}

int is_facing_left(int angle, t_angle *a)
{
	return (angle > a->a90 && angle < a->a270);
}

double	mabs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int destroy(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->window);
	//TODO: destroy images?
	exit(0);
}
