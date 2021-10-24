/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarson <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:52:52 by aarson            #+#    #+#             */
/*   Updated: 2021/10/24 15:52:53 by aarson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"

int	atoc(const char *str)
{
	int	res;
	int	flag;

	res = 0;
	flag = 0;
	while (*str >= 48 && *str <= 57)
	{
		flag = 1;
		res = res * 10 + (*str - '0');
		str++;
	}
	if (!flag || res > 255)
		ft_err("Number collor incorrect");
	return (res);
}

int	valid_color(char *str)
{
	char	**arr;

	arr = ft_split(str, ',');
	if (!arr || len_arr(arr) != 3)
		ft_err("Parse color error");
	return ((atoc(arr[0]) << 16) + (atoc(arr[1]) << 8) + atoc(arr[2]));
}

void	floor_func(t_map *map, int *status, char *path)
{
	printf("floor_func");
	if ((*status & FLOOR) == FLOOR)
		ft_err("Parse error duplicate element");
	*status = *status | FLOOR;
	map->resources.floor = valid_color(path);
}

void	ceil_func(t_map *map, int *status, char *path)
{
	printf("ceil_func");
	if ((*status & CEILING) == CEILING)
		ft_err("Parse error duplicate element");
	*status = *status | CEILING;
	map->resources.ceiling = valid_color(path);
}