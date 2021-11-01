#ifndef MAP_H
# define MAP_H

typedef struct s_resources
{
 	char			*north;
 	char			*south;
 	char			*west;
 	char			*east;
 	unsigned int	floor;
 	unsigned int	ceiling;
}	t_resources;

typedef struct s_map
{
	char	**map;
	int		size[2];
	int		player[2];
	int		player_dir;
	t_resources resources;
}	t_map;

#endif
