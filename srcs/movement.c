/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:50:23 by lemarian          #+#    #+#             */
/*   Updated: 2025/06/02 15:56:40 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	movement(int key_code, t_data *data)//norm!!!
{
	double	old_dir_x;
	double	old_plane_x;
	double	next_x;
	double	next_y;
	t_raycast	*ray;

	ray = data->rc;
	if (key_code == ESC)
		exit_game(data);
	if (key_code == W)
	{
		next_x = data->p_pos.x + ray->p_dir.x * SPEED;
		next_y = data->p_pos.y + ray->p_dir.y * SPEED;
		if (data->map[(int)(data->p_pos.y)][(int)(next_x)] == '0')
			data->p_pos.x = next_x;
		if (data->map[(int)(next_y)][(int)data->p_pos.x] == '0')
			data->p_pos.y = next_y;
	}
	else if (key_code == S)
	{
		next_x = data->p_pos.x - ray->p_dir.x * SPEED;
		next_y = data->p_pos.y - ray->p_dir.y * SPEED;
		if (data->map[(int)(data->p_pos.y)][(int)(next_x)] == '0')
			data->p_pos.x = next_x;
		if (data->map[(int)(next_y)][(int)data->p_pos.x] == '0')
			data->p_pos.y = next_y;
	}
	else if (key_code == D)
	{
		old_dir_x = ray->p_dir.x;
		ray->p_dir.x = ray->p_dir.x * cos(ROT) - ray->p_dir.y * sin(ROT);
		ray->p_dir.y = old_dir_x * sin(ROT) + ray->p_dir.y * cos(ROT);
		old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * cos(ROT) - ray->plane.y * sin(ROT);
		ray->plane.y = old_plane_x * sin(ROT) + ray->plane.y * cos(ROT);
	}
	else if (key_code == A)
	{
		old_dir_x = ray->p_dir.x;
		ray->p_dir.x = ray->p_dir.x * cos(-ROT) - ray->p_dir.y * sin(-ROT);
		ray->p_dir.y = old_dir_x * sin(-ROT) + ray->p_dir.y * cos(-ROT);
		old_plane_x = ray->plane.x;
		ray->plane.x = ray->plane.x * cos(-ROT) - ray->plane.y * sin(-ROT);
		ray->plane.y = old_plane_x * sin(-ROT) + ray->plane.y * cos(-ROT);
	}
	return (0);
}