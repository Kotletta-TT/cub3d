/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_r_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:00:41 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 20:01:35 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_R_DATA_H
# define INIT_R_DATA_H

t_render	*new_r_data(t_cub *cub/* int win_size[2] *//* , int tile_size) */);
t_angle		*init_angles(int width);

#endif
