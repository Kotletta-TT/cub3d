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
	(void)map;
	(void)line;
	if ((*status & START) != START)
		*status = *status | START;
	if (!*line)
		ft_err("Parse error: Empty line inner map");
	printf("valid str map");
}
