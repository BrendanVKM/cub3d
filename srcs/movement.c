/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gael <gael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:50:23 by lemarian          #+#    #+#             */
/*   Updated: 2025/05/29 11:18:25 by gael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	movement(int key_code, t_data *data, t_raycast *rc) // need norme
{
	double	old_dir_x;
	double	old_plane_x;

	if (key_code == W)
	{
		if (data->map[(int)(data->p_pos.y)][(int)((data->p_pos.x + rc->p_dir.x) * SPEED)] == '0')
			data->p_pos.x += rc->p_dir.x * SPEED;
		if (data->map[(int)((data->p_pos.y + rc->p_dir.y) * SPEED)][(int)data->p_pos.x] == '0')
			data->p_pos.y += rc->p_dir.y * SPEED;
	}
	if (key_code == S)
	{
		if (data->map[(int)(data->p_pos.y)][(int)((data->p_pos.x - rc->p_dir.x) * SPEED)] == '0')
			data->p_pos.x -= rc->p_dir.x * SPEED;
		if (data->map[(int)((data->p_pos.y - rc->p_dir.y) * SPEED)][(int)data->p_pos.x] == '0')
			data->p_pos.y -= rc->p_dir.y * SPEED;
	}
	if (key_code == D)
	{
		old_dir_x = rc->p_dir.x;
		rc->p_dir.x = rc->p_dir.x * cos(-ROT) - rc->p_dir.y * sin(-ROT);
		rc->p_dir.y = old_dir_x * sin(-ROT) + rc->p_dir.y * cos(-ROT);
		old_plane_x = rc->plane.x;
		rc->plane.x = rc->plane.x * cos(-ROT) - rc->plane.y * sin(-ROT);
		rc->plane.y = old_plane_x * sin(-ROT) + rc->plane.y * cos(-ROT);
	}
	if (key_code == A)
	{
		old_dir_x = rc->p_dir.x;
		rc->p_dir.x = rc->p_dir.x * cos(ROT) - rc->p_dir.y * sin(ROT);
		rc->p_dir.y = old_dir_x * sin(ROT) + rc->p_dir.y * cos(ROT);
		old_plane_x = rc->plane.x;
		rc->plane.x = rc->plane.x * cos(ROT) - rc->plane.y * sin(ROT);
		rc->plane.y = old_plane_x * sin(ROT) + rc->plane.y * cos(ROT);
	}
	return (0);
}