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
	(void)map;
	
	if ((*status & START) != START)
		*status = *status | START;
	if (!*line)
		ft_err("Parse error: Empty line inner map");
	tmp = malloc(sizeof(char *) * (map->map_cub_size + 2));
	if (!tmp)
		ft_err("Malloc\n");
	i = -1;
	while(++i < map->map_cub_size)
		tmp[i] = map->map[i];
	tmp[i++] = ft_strdup(line);
	tmp[i] = 0;
	map->map_cub_size += 1;
	printf("%d\n", map->map_cub_size);
	free(map->map);
	map->map = tmp;
	printf("valid str map");
}

int	valid_map(t_map *map)
{
	int	i;
	int	k;

	i = -1;
	while (map->map[++i])
	{
		k = 0;
		while(map->map[i][k])
		{
			
		}
	}
}
