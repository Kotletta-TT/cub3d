/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:46:58 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 21:22:02 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_UTILS_H
# define EVENT_UTILS_H

int		calc_angle(t_cub *cub, int flags);
void	movement_event(t_cub *cub);
void	turn_event(t_cub *cub);
// void	turn_event_mouse(t_cub *cub);

#endif 
