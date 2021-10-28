/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarson <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:46:58 by aarson            #+#    #+#             */
/*   Updated: 2021/10/24 12:47:00 by aarson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

void	valid_str_map(t_map *map, char *line, int *status)
{
	char	**tmp;
	int		i;

	if ((*status & START) != START)
		*status = *status | START;
	if (!*line)
		ft_err("Parse error: Empty line inner map");
	tmp = malloc(sizeof(char *) * (map->player_dir + 2));
	if (!tmp)
		ft_err("Malloc\n");
	i = -1;
	while (++i < map->player_dir)
		tmp[i] = map->map[i];
	tmp[i++] = ft_strdup(line);
	tmp[i] = 0;
	map->player_dir += 1;
	printf("%d\n", map->player_dir);
	free(map->map);
	map->map = tmp;
	printf("valid str map");
}

void	check_outer_borders(char **map)
{
	int	i;
	int	k;

	i = -1;
	while (map[0][++i])
		if (map[0][i] != '1' && map[0][i] != ' ')
			ft_err("Invalid map");
	k = len_arr(map) - 1;
	i = -1;
	while (map[k][++i])
		if (map[k][i] != '1' && map[k][i] != ' ')
			ft_err("Invalid map");
	i = -1;
	while (map[++i])
		if (map[i][0] != '1' && map[i][0] != ' ')
			ft_err("Invalid map");
	i = -1;
	while (map[++i])
		if ((map[i][ft_strlen(map[i]) - 1] != '1')
		&& (map[i][ft_strlen(map[i]) - 1] != ' '))
			ft_err("Invalid map");
}

void	check_unnecesary_sym(char **map)
{
	char	*sym;
	int		i;
	int		k;

	sym = ft_strdup("01 WESN");
	if (!sym)
		ft_err("Malloc error");
	i = -1;
	while (map[++i])
	{
		k = -1;
		while (map[i][++k])
			if (!(ft_strchr(sym, map[i][k])))
				ft_err("Incorrect type symbol in map");
	}
	free(sym);
}

void	check_correct_pos(char **map, int x, int y)
{
	int	prev_len;
	int	next_len;

	prev_len = ft_strlen(map[y - 1]);
	next_len = ft_strlen(map[y + 1]);
	if (x <= prev_len || x <= next_len)
	{
		printf("y:%d x:%d", x, y);
		ft_err("Map not closed");
	}
	if (map[y - 1][x - 1] == ' ' || map[y - 1][x] == ' ' || map[y - 1][x + 1]
	 == ' ' || map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || map[y + 1]
	[x - 1] == ' ' || map[y + 1][x] == ' ' || map[y + 1][x + 1] == ' ')
	{
		printf("y:%d x:%d", x, y);
		ft_err("Map not closed");
	}
}

void	get_player_pos(t_map *map, int x, int y, char dir)
{
	map->player[0] = x;
	map->player[1] = y;
	if (dir == 'N')
		map->player_dir = 90;
	else if (dir == 'S')
		map->player_dir = 270;
	else if (dir == 'W')
		map->player_dir = 180;
	else
		map->player_dir = 0;
}

void	check_player_availability(t_map *map)
{
	int		x;
	int		y;
	char	*player_type;

	player_type = ft_strdup("WESN");
	if (!player_type)
		ft_err("Malloc error");
	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (ft_strchr(player_type, map->map[y][x]))
				{
					check_correct_pos(map->map, x, y);
					get_player_pos(map, x, y,  map->map[y][x]);
					return ;
				}
		}
		
	}
	free(player_type);
	ft_err("No player in map");
}

void	check_zeroes(char **map)
{
	int	i;
	int	k;

	i = -1;
	while (map[++i])
	{
		k = -1;
		while(map[i][++k])
		{
			if (map[i][k] == '0')
				check_correct_pos(map, k, i);
		}
	}
}

int	valid_map(t_map *map)
{
	check_unnecesary_sym(map->map);
	check_outer_borders(map->map);
	check_player_availability(map);
	check_zeroes(map->map);
	return(1);
	// while (map->map[++i])
	// {
	// 	k = 0;
	// 	while(map->map[i][k])
	// 	{
			
	// 	}
	// }
}
