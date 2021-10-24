/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarson <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:38:46 by aarson            #+#    #+#             */
/*   Updated: 2021/10/24 19:38:52 by aarson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
		ft_err("Bad argument");
	if (!(init_map(&map)) || !(check_ext(av[1], ".cub")) || !(parse_map(map,
				av[1])))
		ft_err("Error");
	return (0);
}
