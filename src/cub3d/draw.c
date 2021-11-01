#include "render.h"
#include "draw.h"

int	scale(double from, double to, double value)
{
	return ((int)floor(to * value/from));
}

unsigned int	get_pixel(t_cub *cub, t_slice *slice)
{
	t_ray	*ray;
	int		tile_size;
	int		place[2];
	int		xpm_size;

	// printf("slice_x: %i, slice_y: %i, slice_len: %i\n", slice_x, slice_y, slice_len);
	ray = &cub->r_data->rays[slice->x];
	tile_size = cub->map3d->tile_size;
	xpm_size = cub->textures[ray->t_idx].size[0];
	place[0] = scale(tile_size, xpm_size, ray->offset);
	place[1] = scale(slice->len, xpm_size, slice->y);
	// printf("xpm place: %i, %i\n", place[0], place[1]);
	return (cub->textures[ray->t_idx].pixels[place[1] * xpm_size + place[0]]);
}

void	draw_ceiling(t_cub *cub, t_slice *slice)
{
	int		i;
	t_image	*map_img;

	map_img = cub->map3d->img;
	i = slice->x;
	while (i < slice->top)
	{
		map_img->pixels[i] = cub->map->resources.ceiling;
		i += map_img->size[0];
	}
}

void	draw_floor(t_cub *cub, t_slice *slice)
{
	int		i;
	t_image	*map_img;

	map_img = cub->map3d->img;
	i = slice->bottom;
	while (i < map_img->capacity)
	{
		map_img->pixels[i] = cub->map->resources.floor;
		i += map_img->size[0];
	}
}

void	draw_wall(t_cub *cub, t_slice *slice)
{
	int		i;
	t_image	*map_img;

	i = slice->top;
	map_img = cub->map3d->img;
	while (i < slice->bottom)
	{
		map_img->pixels[i] = get_pixel(cub, slice);
		i += map_img->size[0];
		slice->y++;
	}
}

void	draw_slice(t_image *map_img, t_slice *slice, t_cub *cub)
{
	if (slice->len >= map_img->size[1])
	{
		slice->top = slice->x;
		slice->bottom = slice->x + map_img->capacity - 1;
		slice->y = (slice->len - map_img->size[1]) >> 1;
	}
	else
	{
		slice->top = ((map_img->size[1] >> 1) - (slice->len >> 1)) * map_img->size[0]
			+ slice->x;
		slice->bottom = ((map_img->size[1] >> 1) + (slice->len >> 1)) * map_img->size[0]
			+ slice->x;
		slice->y = 0;
	}
	draw_wall(cub, slice);
	draw_floor(cub, slice);
	draw_ceiling(cub, slice);
}

void	draw(t_cub *cub)
{
	int		i;
	double	ray_len;
	t_slice	slice;

	i = -1;
	while (++i < cub->win_size[0])
	{
		ray_len = cub->r_data->rays[i].len;
		slice.len = round(cub->map3d->tile_size/*  * cub->r_data->res_ratio */ / ray_len * cub->r_data->dist_to_scrn);
		slice.x = i;
		draw_slice(cub->map3d->img, &slice, cub);
	}
	mlx_put_image_to_window(cub->mlx, cub->window, cub->map3d->img->img, 0, 0);
}
