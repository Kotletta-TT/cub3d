#include "render.h"

int	is_wall(t_cub *cub, double *point, double angle)
{
	int		x_map;
	int		y_map;
	t_map	*map;

	map = cub->map;
	if (is_facing_left(angle, cub->angles))
		x_map = (int)ceil(point[0]) >> cub->map3d->log;
	else
		x_map = (int)floor(point[0]) >> cub->map3d->log;
	if (is_facing_up(angle, cub->angles))
		y_map = (int)ceil(point[1]) >> cub->map3d->log;
	else
		y_map = (int)floor(point[1]) >> cub->map3d->log;
	if (x_map < 0 || x_map >= map->size[0] || y_map < 0 || y_map >= map->size[1])
		return (-1);
	// printf("is_wall(x, y): %i, %i, point(%lf, %lf), map->size(%i, %i)\n", x_map, y_map, point[0], point[1], map->size[0], map->size[1]);
	// printf("map[%i]: %s, map->size(%i, %i)\n", y_map, map->map[y_map],
	// 	map->size[0], map->size[1]);
	if (map->map[y_map][x_map] == '1')
	{
		// if (debug && d2)
			// printf("is_wall(x, y): %i, %i, point(%lf, %lf), map->size(%i, %i)\n",
		// printf("test1\n");
			// 	x_map, y_map, point[0], point[1], map->size[0], map->size[1]);
		return (1);
	}
	return (0);
}

int find_first_horizontal(t_cub *cub, int angle, double *fp)
{
	int		opposite;
	int		*player;
	int		log;

	player = cub->map3d->player;
	log = cub->map3d->log;
	if (angle == 0 || angle == cub->angles->a180)
		return (-1);
	if (is_facing_up(angle, cub->angles))
		fp[1] = ((player[1] >> log) << log) - 1;
	else
		fp[1] = ((player[1] >> log) << log) + cub->map3d->tile_size;
	opposite = player[1] - fp[1];
	if (is_facing_left(angle, cub->angles))
		fp[0] = player[0] - mabs(opposite * cub->r_data->values->itan[angle]/* / tan(to_radians(angle)) */);
	else
		fp[0] = player[0] + mabs(opposite * cub->r_data->values->itan[angle]/* / tan(to_radians(angle)) */);
	return (0);
}

int find_first_vertical(t_cub *cub, int angle, double *fp)
{
	int		adjacent;
	int		*player;
	int		log;

	player = cub->map3d->player;
	log = cub->map3d->log;
	if (angle == cub->angles->a90 || angle == cub->angles->a270)
		return (-1);
	if (is_facing_left(angle, cub->angles))
		fp[0] = ((player[0] >> log) << log) - 1;
	else
		fp[0] = ((player[0] >> log) << log) + cub->map3d->tile_size;
	adjacent = player[0] - fp[0];
	if (is_facing_up(angle, cub->angles))
		fp[1] = player[1] - mabs(adjacent * cub->r_data->values->tan[angle]/* tan(to_radians(angle)) */);
	else
		fp[1] = player[1] + mabs(adjacent * cub->r_data->values->tan[angle]/* tan(to_radians(angle)) */);
	return (0);
}

double	cast_horizontal(t_cub *cub, int angle, double *next_point/* , int index */)
{
	double	xA;
	double	yA;
	int		wall_check;

	if (find_first_horizontal(cub, angle, next_point) == -1)
		return (INFINITY);
	if (is_facing_up(angle, cub->angles)) 
		yA = -cub->map3d->tile_size;
	else
		yA = cub->map3d->tile_size;
	if (is_facing_left(angle, cub->angles))
		xA = -cub->r_data->values->xA[angle]/* mabs(yA / tan(to_radians(angle))) */;
	else
		xA = cub->r_data->values->xA[angle]/* mabs(yA / tan(to_radians(angle))) */;
	wall_check = is_wall(cub, next_point, angle);
	while (wall_check == 0)
	{
		next_point[0] += xA;
		next_point[1] += yA;
		wall_check = is_wall(cub, next_point, angle);
	}
	if (wall_check == -1)
		return (INFINITY);
	// printf("horizontal end\n");
	return (mabs((cub->map3d->player[1] - next_point[1]) * cub->r_data->values->isin[angle] /* / sin(to_radians(angle)) */));
}

double	cast_vertical(t_cub *cub, int angle, double *next_point/* , int index */)
{
	double	xA;
	double	yA;
	int		wall_check;

	// (void) index;
	if (find_first_vertical(cub, angle, next_point) == -1)
		return (INFINITY);
	// printf("fp: %i, %i\n", next_point[0], next_point[1]);
	if (is_facing_left(angle, cub->angles))
		xA = -cub->map3d->tile_size;
	else
		xA = cub->map3d->tile_size;
	if (is_facing_up(angle, cub->angles))
		yA = -cub->r_data->values->yA[angle]/* mabs(xA * tan(to_radians(angle))) */;
	else
		yA = cub->r_data->values->yA[angle]/* mabs(xA * tan(to_radians(angle))) */;
	wall_check = is_wall(cub, next_point, angle);
	while (wall_check == 0)
	{
		next_point[0] += xA;
		next_point[1] += yA;
		wall_check = is_wall(cub, next_point, angle);
	}
	if (wall_check == -1)
		return (INFINITY);
	// printf("vertical end\n");
	return (mabs((cub->map3d->player[0] - next_point[0]) * cub->r_data->values->icos[angle] /* / cos(to_radians(angle)) */));
}

int	get_texture_id(int horizontal, int angle, t_angle *a)
{
	if (horizontal && is_facing_up(angle, a))
		return (NORTH);
	else if (horizontal)
		return (SOUTH);
	else if (!horizontal && is_facing_left(angle, a))
		return (WEST);
	else
		return (EAST);
}

void	render_ray(t_cub *cub, int angle, t_ray *ray/* , int index */)
{
	double	h_dist;
	double	v_dist;
	double	h_point[2];
	double	v_point[2];
	int		relative_angle;

	relative_angle = (int)mabs(angle - cub->map->player_dir);
	h_dist = cast_horizontal(cub, angle, h_point/* , index */);
	v_dist = cast_vertical(cub, angle, v_point/* , index */);
	// printf("h_dist: %lf, v_dist: %lf\n", h_dist, v_dist);
	if (h_dist < v_dist)
	{
		ray->len = h_dist * cub->r_data->values->fish[relative_angle];//cub->angle->fish[angle] //* mabs(cos(to_radians(relative_angle)));
		ray->offset = (int)round(h_point[0]) % cub->map3d->tile_size;
		ray->t_idx = get_texture_id(1, angle, cub->angles);
		// printf("HORIZONTAL: texture: %i, angle: %lf\n", ray->t_idx, angle);
	}
	else
	{
		ray->len = v_dist * cub->r_data->values->fish[relative_angle];//cub->angle->fish[angle] //* mabs(cos(to_radians(relative_angle)));
		ray->offset = (int)round(v_point[1]) % cub->map3d->tile_size;
		ray->t_idx = get_texture_id(0, angle, cub->angles);
		// printf("VERTICAL: texture: %i, angle: %lf\n", ray->t_idx, angle);
	}
}

void	cast_rays(t_cub *cub)
{
	int	angle;
	int	i;
	// int	index;

	i = -1;
	// printf("player(%i, %i), player_dir: %i\n", cub->map3d->player[0],
	// 	cub->map3d->player[1], cub->map->player_dir);
	// angle = cub->map->player_dir + (FOV >> 1);
	angle = cub->map->player_dir + cub->angles->a30;
	// printf("angle before: %i\n", angle);
	if (angle > cub->angles->a360)
		angle = angle % cub->angles->a360;
	// index = (int)round(angle / cub->r_data->angle);
	// printf("angle: %lf, dif: %lf, index(floor): %lf, index(ceil): %lf, index(original): %lf\n",	angle, cub->r_data->angle, floor(angle / cub->r_data->angle),
	// 	ceil(angle / cub->r_data->angle),
	// 	angle / cub->r_data->angle);
	// printf("count: %i, first angle: %lf, player_dir: %i, index: %i, angle_dif: %lf, ", 
	// 	cub->r_data->count, angle, cub->map->player_dir, index, cub->r_data->angle);
	// printf("angle after: %lf\n", angle);
	while (++i < cub->r_data->count)
	{
		// index = index % cub->r_data->cnt360;
		render_ray(cub, angle, &cub->r_data->rays[i]/* , index */);
		// angle -= cub->r_data->angle;
		angle--;
		if (angle < 0)
			angle = cub->angles->a360 + angle;
		// index++;
	}
	// printf("last_index: %i\n", index);
	// printf("last angle: %i, player_dir: %i\n", angle, cub->map->player_dir);
}
