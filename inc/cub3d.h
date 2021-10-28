#ifndef CUB3D_H
# define CUB3D_H
typedef struct s_resources
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    unsigned int     floor;
    unsigned int     ceiling;
}   t_resources;
typedef struct s_map
{
    char        **map;
    int         size[2];
    int         player[2];
    int         player_dir;
    t_resources resources;
}   t_map;
typedef struct s_arr_func
{
	char	name;
	void	(*f)(t_map *, int *, char *);
}	t_arr_func;
#define FLOOR   1
#define CEILING 2
#define EAST    4
#define WEST    8
#define SOUTH   16
#define NORTH   32
#define MAP     63
#define START   128
#include <stdio.h>
/* Parse */
int         init_map(t_map **map);
void	    ft_err(char *message);
int         check_open(char *path);
int         check_ext(char *path, char *ext);
void	    open_file(char *path, int *fd);
void        floor_func(t_map *map, int *status, char *path);
void        ceil_func(t_map *map, int *status, char *path);
int		    len_arr(char **arr);
void	    free_arr(char **name);
void        ea_func(t_map *map, int *status, char *path);
void        we_func(t_map *map, int *status, char *path);
void        so_func(t_map *map, int *status, char *path);
void        no_func(t_map *map, int *status, char *path);
void	    valid_str_map(t_map *map, char *line, int *status);
int		    parse_map(t_map *map, char *path);
void	    parse_string(t_map *map, char *line, int *status);
char	    **init_names(void);
void	    valid_elem_str(t_map *map, char *line, int *status);
void	    free_names(char **name);
int			valid_map(t_map *map);
#endif


/* 00000000 00000000 00000000 00000000

00000000 11111111 00000000 00000000

00000000 00000000 11111111 00000000

00000000 00000000 00000000 11111111

255 64 64

floor_color = (255 << 16) + (64 << 8) + 64; */


/* status = status | FLOOR; */
	/*	00000000
		00000001
		00000001 */
		/* status = status | CEILING; */
	/*	00000001
		00000010
		00000011 */

		/* if (status & CEILING == CEILING) */
	/*	00000011
		00000010
		00000010 */