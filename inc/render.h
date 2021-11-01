#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <math.h>
# include <stdio.h> //TODO: remove?
# include <stdlib.h>
# include "map.h"

enum	e_texture {NORTH, SOUTH, WEST, EAST};

typedef struct s_image
{
	void			*img;
	unsigned int	*pixels;
	int				size[2];
	int				capacity;
	int				bits_per_pixel;
	int				size_line;
	int				is_big_endian;
}	t_image;

typedef struct s_minimap
{
	t_image	*img;
	int		tile_size;
	int		player_icon_radius;
}	t_minimap;

typedef struct s_map3d
{
	t_image	*img;
	int		player[2];
	int		tile_size;
	int		log;
}	t_map3d;

typedef struct s_ray
{
	double			len;
	int				offset;
	enum e_texture	t_idx;
}	t_ray;

typedef struct s_values
{
	double	*sin;
	double	*cos;
	double	*isin;
	double	*icos;
	double	*tan;
	double	*itan;
	double	*fish;
	double	*xA;
	double	*yA;
	int		*m_stepX;
	int		*m_stepY;
}	t_values;

typedef struct s_angle
{
	int	a60;
	int	a30;
	int	a360;
	int	a90;
	int	a180;
	int	a270;
	int	a15;
	int	a5;
	int	a45;
}	t_angle;
typedef struct s_render
{
	// float		res_ratio;
	double		dist_to_scrn;
	int			count;
	int			cnt360;
	double		angle;
	t_ray		*rays;
	t_values	*values;
}	t_render;

typedef struct s_cub
{
	void		*mlx;
	void		*window;
	int			win_size[2];
	t_map		*map;
	t_map3d		*map3d;
	t_minimap	*minimap;
	t_render	*r_data;
	int			mov_flags;
	int			turn_flags;
	t_image		*textures;
	t_angle		*angles;
}	t_cub;

double	to_radians(double degree);
double	to_degrees(double radians);
void	init_cub(t_cub *cub, t_map *map);
int		is_facing_up(int angle, t_angle *a);
int		is_facing_left(int angle, t_angle *a);
double	mabs(double n);
void	cast_rays(t_cub *cub);
int		destroy(t_cub *cub);
int		key_hook(int keycode, t_cub *cub);
int		key_pressed(int keycode, t_cub *cub);
int		key_released(int keycode, t_cub *cub);
int		loop_hook(t_cub *cub);
void	draw(t_cub *cub);
void	start(t_map *map);
void	ft_err(char *message);
#endif
