/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:50:23 by lemarian          #+#    #+#             */
/*   Updated: 2025/05/02 12:01:24 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//wip based on lodev
//key_release?

void	movement(t_data *data, t_raycast *rc, int keypress)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keypress = W)
	{
		if (!data->map[(int)(data->p_pos.x + rc->p_dir.x) * SPEED][(int)(data->p_pos.y)])
			data->p_pos.x += rc->p_dir.x * SPEED;
		if (!data->map[(int)(data->p_pos.y)][(int)(data->p_pos.y + rc->p_dir.y) * SPEED])
			data->p_pos.y += rc->p_dir.y * SPEED;
	}
	if (keypress = S)
	{
		if (!data->map[(int)(data->p_pos.x - rc->p_dir.x) * SPEED][(int)(data->p_pos.y)])
			data->p_pos.x -= rc->p_dir.x * SPEED;
		if (!data->map[(int)(data->p_pos.y)][(int)(data->p_pos.y - rc->p_dir.y) * SPEED])
			data->p_pos.y -= rc->p_dir.y * SPEED;
	}
	if (keypress = D)
	{
		old_dir_x = rc->p_dir.x;
		rc->p_dir.x = rc->p_dir.x * cos(-ROT) - rc->p_dir.y * sin(-ROT);
		rc->p_dir.y = old_dir_x * sin(-ROT) + rc->p_dir.y * cos(-ROT);
		old_plane_x = rc->plane.x;
		rc->plane.x = rc->plane.x * cos(-ROT) - rc->plane.y * sin(-ROT);
		rc->plane.y = old_plane_x * sin(-ROT) + rc->plane.y * cos(-ROT);
	}
	if (keypress = A)
	{
		old_dir_x = rc->p_dir.x;
		rc->p_dir.x = rc->p_dir.x * cos(ROT) - rc->p_dir.y * sin(ROT);
		rc->p_dir.y = old_dir_x * sin(ROT) + rc->p_dir.y * cos(ROT);
		old_plane_x = rc->plane.x;
		rc->plane.x = rc->plane.x * cos(ROT) - rc->plane.y * sin(ROT);
		rc->plane.y = old_plane_x * sin(ROT) + rc->plane.y * cos(ROT);
	}
}