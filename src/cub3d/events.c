#include "render.h"
#include "events.h"
#include "settings.h"
#include "libft.h"

void	movement_event(t_cub *cub)
{
	int			angle;
	int			flags;

	flags = cub->mov_flags;
	if ((flags & M_LEFT) == M_LEFT && (flags & M_RIGHT) == M_RIGHT)
		flags = (flags ^ M_LEFT) & (flags ^ M_RIGHT);
	if ((flags & M_FORWARD) == M_FORWARD
		&& (flags & M_BACKWARDS) == M_BACKWARDS)
		flags = (flags ^ M_FORWARD) & (flags ^ M_BACKWARDS);
	if ((flags & M_LEFT) == M_LEFT 
		&& (flags & M_FORWARD) == M_FORWARD)
		angle = cub->map->player_dir + cub->angles->a45;
	else if ((flags & M_LEFT) == M_LEFT 
		&& (flags & M_BACKWARDS) == M_BACKWARDS)
		angle = cub->map->player_dir + cub->angles->a90 + cub->angles->a45;
	else if ((flags & M_LEFT) == M_LEFT)
		angle = cub->map->player_dir + cub->angles->a90;
	else if ((flags & M_RIGHT) == M_RIGHT
		&& (flags & M_FORWARD) == M_FORWARD)
		angle = cub->map->player_dir - cub->angles->a45;
	else if ((flags & M_RIGHT) == M_RIGHT
		&& (flags & M_BACKWARDS) == M_BACKWARDS)
		angle = cub->map->player_dir + cub->angles->a180 + cub->angles->a45;
	else if ((flags & M_RIGHT) == M_RIGHT)
		angle = cub->map->player_dir - cub->angles->a90;
	else if ((flags & M_BACKWARDS) == M_BACKWARDS)
		angle = cub->map->player_dir + cub->angles->a180;
	else if ((flags & M_FORWARD) == M_FORWARD)
		angle = cub->map->player_dir;
	else
		return ;
	angle = angle % cub->angles->a360;
	if (angle < 0)
		angle = cub->angles->a360 + angle;
	if (is_facing_left(angle, cub->angles))
		cub->map3d->player[0] -= cub->r_data->values->m_stepX[angle];
	else
		cub->map3d->player[0] += cub->r_data->values->m_stepX[angle];
	if (is_facing_up(angle, cub->angles))
		cub->map3d->player[1] -= cub->r_data->values->m_stepY[angle];
	else
		cub->map3d->player[1] += cub->r_data->values->m_stepY[angle];
}

int key_pressed(int keycode, t_cub *cub)
{
	if (keycode == ARROW_LEFT)
		cub->turn_flags = cub->turn_flags | T_LEFT;
	else if (keycode == ARROW_RIGHT)
		cub->turn_flags = cub->turn_flags | T_RIGHT;
	else if (keycode == A)
		cub->mov_flags = cub->mov_flags | M_LEFT;
	else if (keycode == D)
		cub->mov_flags = cub->mov_flags | M_RIGHT;
	else if (keycode == W)
		cub->mov_flags = cub->mov_flags | M_FORWARD;
	else if (keycode == S)
		cub->mov_flags = cub->mov_flags | M_BACKWARDS;
	else if (keycode == 53)
		destroy(cub);
	return (0);
}

int key_released(int keycode, t_cub *cub)
{
	if (keycode == ARROW_LEFT)
		cub->turn_flags = cub->turn_flags ^ T_LEFT;
	else if (keycode == ARROW_RIGHT)
		cub->turn_flags = cub->turn_flags ^ T_RIGHT;
	else if (keycode == A)
		cub->mov_flags = cub->mov_flags ^ M_LEFT;
	else if (keycode == D)
		cub->mov_flags = cub->mov_flags ^ M_RIGHT;
	else if (keycode == W)
		cub->mov_flags = cub->mov_flags ^ M_FORWARD;
	else if (keycode == S)
		cub->mov_flags = cub->mov_flags ^ M_BACKWARDS;
	return (0);
}

void	turn_event(t_cub *cub)
{
	const int	step = TURN_SPEED * (cub->angles->a5 / 10);

	if ((cub->turn_flags & T_LEFT) == T_LEFT
		&& (cub->turn_flags & T_RIGHT) == T_RIGHT)
		return ;
	if ((cub->turn_flags & T_LEFT) == T_LEFT)
		cub->map->player_dir = (cub->map->player_dir + step) % 
			cub->angles->a360;
	else if ((cub->turn_flags & T_RIGHT) == T_RIGHT)
	{
		cub->map->player_dir -= step;
		if (cub->map->player_dir < 0)
			cub->map->player_dir = cub->angles->a360
				+ cub->map->player_dir;
	}
}

int	loop_hook(t_cub *cub)
{
	if (cub->mov_flags)
		movement_event(cub);
	if (cub->turn_flags)
		turn_event(cub);
	ft_bzero(cub->map3d->img->pixels,
		sizeof(unsigned int) * cub->map3d->img->capacity);
	mlx_clear_window(cub->mlx, cub->window);
	cast_rays(cub);
	draw(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->map3d->img->img, 0, 0);
	return (0);
}
