#include "render.h"
#include "events.h"
#include "settings.h"
#include "mlx.h"

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_err("mlx_init failed\n");
	cub->win_size[0] = DEFAULT_WIDTH;
	cub->win_size[1] = DEFAULT_HEIGHT;
	if (DEFAULT_WIDTH < MIN_WIDTH)
		cub->win_size[0] = MIN_WIDTH;
	else if (DEFAULT_WIDTH > MAX_WIDTH)
		cub->win_size[0] = MAX_WIDTH;
	if (DEFAULT_HEIGHT < MIN_HEIGHT)
		cub->win_size[1] = MIN_HEIGHT;
	else if (DEFAULT_HEIGHT > MAX_HEIGHT)
		cub->win_size[1] = MAX_HEIGHT;
	cub->window = mlx_new_window(cub->mlx, cub->win_size[0], cub->win_size[1],
		NAME);
	if (!cub->window)
		ft_err("mlx_new_window failed\n");
}

t_image	*new_image(void *mlx, int *win_size, char *xpm)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (!image)
		ft_err("malloc failed\n");
	if (xpm)
		image->img = mlx_xpm_file_to_image(mlx, xpm, &image->size[0], &image->size[1]);
	else
		image->img = mlx_new_image(mlx, win_size[0], win_size[1]);
	if (!image->img)
		ft_err("mlx_new_image failed\n");
	image->pixels = (unsigned int *)mlx_get_data_addr(image->img,
		&image->bits_per_pixel, &image->size_line, &image->is_big_endian);
	if (!xpm)
	{
		image->size[0] = win_size[0];
		image->size[1] = win_size[1];
	}
	image->capacity = image->size[0] * image->size[1];
	return (image);
}

t_map3d	*new_map3d(void *mlx, int *win_size, int raw_player[2])
{
	t_map3d	*map3d;

	map3d = malloc(sizeof(t_map3d));
	if (!map3d)
		ft_err("mlx_init failed\n");
	map3d->img = new_image(mlx, win_size, 0);
	map3d->log = (int)round(log2(win_size[0])) - 2;
	map3d->tile_size = 1 << map3d->log;
	// printf("log: %i, tile_size: %i\n", map3d->log, map3d->tile_size);
	map3d->player[0] = raw_player[0] * map3d->tile_size
		+ (map3d->tile_size >> 1);
	map3d->player[1] = raw_player[1] * map3d->tile_size
		+ (map3d->tile_size >> 1);
	return (map3d);
}

t_minimap	*new_minimap(void *mlx, int *win_size)
{
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	if (!minimap)
		ft_err("malloc failed\n");
	minimap->tile_size = 1; //TODO: calculate tile_size
	minimap->player_icon_radius = 2; //TODO: calc player icon radius
	minimap->img = new_image(mlx, win_size, 0); //TODO: calculate img size
	return (minimap);
}

void	fill_values(t_values *vals, int cnt, double angle, int tile_size)
{
	int		i;
	double	a;

	i = -1;
	a = 0;
	while (++i < cnt)
	{
		vals->sin[i] = sin(a);
		vals->cos[i] = cos(a);
		vals->isin[i] = 1 / sin(a);
		vals->icos[i] = 1 / cos(a);
		vals->tan[i] = tan(a);
		vals->itan[i] = 1 / tan(a);
		vals->fish[i] = mabs(vals->cos[i]);
		vals->xA[i] = mabs(tile_size * vals->itan[i]);
		vals->yA[i] = mabs(tile_size * vals->tan[i]);
		vals->m_stepX[i] = (int)mabs(round(16 * MOVE_SPEED * vals->cos[i]));
		vals->m_stepY[i] = (int)mabs(round(16 * MOVE_SPEED * vals->sin[i]));
		a += angle;
	}
}

t_values	*init_values(int cnt, double angle, int tile_size)
{
	t_values	*vals;

	vals = malloc(sizeof(t_values));
	if (!vals)
		ft_err("malloc failed\n");
	vals->sin = malloc(sizeof(double) * cnt);
	vals->cos = malloc(sizeof(double) * cnt);
	vals->isin = malloc(sizeof(double) * cnt);
	vals->icos = malloc(sizeof(double) * cnt);
	vals->tan = malloc(sizeof(double) * cnt);
	vals->itan = malloc(sizeof(double) * cnt);
	vals->fish = malloc(sizeof(double) * cnt);
	vals->xA = malloc(sizeof(double) * cnt);
	vals->yA = malloc(sizeof(double) * cnt);
	vals->m_stepX = malloc(sizeof(int) * cnt);
	vals->m_stepY = malloc(sizeof(int) * cnt);
	if (!vals->sin || !vals->cos || !vals->isin || !vals->icos || !vals->tan
		|| !vals->itan || !vals->fish || !vals->xA || !vals->yA
		|| !vals->m_stepX || !vals->m_stepY)
		ft_err("malloc failed\n");
	fill_values(vals, cnt, to_radians(angle), tile_size);
	return (vals);
}

t_angle	*init_angles(int width)
{
	t_angle	*angles;

	angles = malloc(sizeof(t_angle));
	if (!angles)
		ft_err("malloc failed\n");
	angles->a60 = width;
	angles->a30 = angles->a60 / 2;
	angles->a360 = angles->a60 * 6;
	angles->a90 = angles->a30 * 3;
	angles->a180 = angles->a60 * 3;
	angles->a270 = angles->a90 * 3;
	angles->a15 = angles->a30 / 2;
	angles->a45 = angles->a15 * 3;
	angles->a5 = angles->a30 / 6;
	// printf("60: %i\n30: %i\n360 %i\n90: %i\n180: %i\n270: %i\n15: %i"
	// 	"\n45: %i\n5: %i\n", angles->a60, angles->a30, angles->a360,
	// 	angles->a90, angles->a180, angles->a270, angles->a15, angles->a45,
	// 	angles->a5);
	return (angles);
}

t_render	*new_r_data(int win_size[2], int tile_size)
{
	t_render	*r_data;

	r_data = malloc(sizeof(t_render));
	if (!r_data)
		ft_err("malloc failed\n");
	r_data->count = win_size[0];
	r_data->cnt360 = win_size[0] * (360 / FOV);
	// printf("cnt360: %i\n", r_data->cnt360);
	// r_data->res_ratio = (win_size[1] * 1.0) / win_size[0];
	r_data->dist_to_scrn = (win_size[0] >> 1) * 1.0 / tan(to_radians(FOV >> 1));
	r_data->angle = (FOV * 1.0) / win_size[0];
	r_data->rays = malloc(sizeof(t_ray) * win_size[0]);
	if (!r_data->rays)
		ft_err("malloc failed\n");
	//TODO: malloc sins, cosins, tans and fill with precomputed values
	r_data->values = init_values(win_size[0] * (360 / FOV), r_data->angle, 
		tile_size);
	return (r_data);
}

t_image	*init_textures(void *mlx, t_resources *resources)
{
	t_image	*textures;

	textures = malloc(sizeof(t_image) * 4);
	if (!textures)
		ft_err("malloc failed\n");
	textures[NORTH] = *new_image(mlx, 0, resources->north); //FIXME: leaking memory????
	textures[SOUTH] = *new_image(mlx, 0, resources->south);
	textures[WEST] = *new_image(mlx, 0, resources->west);
	textures[EAST] = *new_image(mlx, 0, resources->east);
	return (textures);
}

void	init_player_dir(int *player_dir, t_angle *angle)
{
	if (*player_dir == 90)
		*player_dir = angle->a90;
	else if (*player_dir == 180)
		*player_dir = angle->a180;
	else if (*player_dir == 270)
		*player_dir = angle->a270;
	else
		*player_dir = 0;
}

void	init_cub(t_cub *cub, t_map *map)
{
	// init_map(&cub->map, map);
	cub->map = map;
	init_mlx(cub);
	cub->map3d = new_map3d(cub->mlx, cub->win_size, cub->map->player);
	cub->minimap = new_minimap(cub->mlx,  cub->win_size);
	cub->r_data = new_r_data(cub->win_size, cub->map3d->tile_size);
	cub->mov_flags = 0;
	cub->turn_flags = 0;
	cub->textures = init_textures(cub->mlx, &cub->map->resources);
	cub->angles = init_angles(cub->win_size[0]);
	init_player_dir(&cub->map->player_dir, cub->angles);
}
