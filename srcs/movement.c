/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:50:23 by lemarian          #+#    #+#             */
/*   Updated: 2025/06/05 13:45:00 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	forward(t_data *data, t_raycast *rc)
{
	double	next_x;
	double	next_y;

	next_x = data->p_pos.x + rc->p_dir.x * SPEED;
	next_y = data->p_pos.y + rc->p_dir.y * SPEED;
	if (data->map[(int)(data->p_pos.y)][(int)(next_x)] == '0')
		data->p_pos.x = next_x;
	if (data->map[(int)(next_y)][(int)data->p_pos.x] == '0')
		data->p_pos.y = next_y;
}

void	backward(t_data *data, t_raycast *rc)
{
	double	next_x;
	double	next_y;

	next_x = data->p_pos.x - rc->p_dir.x * SPEED;
	next_y = data->p_pos.y - rc->p_dir.y * SPEED;
	if (data->map[(int)(data->p_pos.y)][(int)(next_x)] == '0')
		data->p_pos.x = next_x;
	if (data->map[(int)(next_y)][(int)data->p_pos.x] == '0')
		data->p_pos.y = next_y;
}

void	left(t_raycast *rc)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = rc->p_dir.x;
	rc->p_dir.x = rc->p_dir.x * cos(-ROT) - rc->p_dir.y * sin(-ROT);
	rc->p_dir.y = old_dir_x * sin(-ROT) + rc->p_dir.y * cos(-ROT);
	old_plane_x = rc->plane.x;
	rc->plane.x = rc->plane.x * cos(-ROT) - rc->plane.y * sin(-ROT);
	rc->plane.y = old_plane_x * sin(-ROT) + rc->plane.y * cos(-ROT);
}

void	right(t_raycast *rc)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = rc->p_dir.x;
	rc->p_dir.x = rc->p_dir.x * cos(ROT) - rc->p_dir.y * sin(ROT);
	rc->p_dir.y = old_dir_x * sin(ROT) + rc->p_dir.y * cos(ROT);
	old_plane_x = rc->plane.x;
	rc->plane.x = rc->plane.x * cos(ROT) - rc->plane.y * sin(ROT);
	rc->plane.y = old_plane_x * sin(ROT) + rc->plane.y * cos(ROT);
}

int	movement(int key_code, t_data *data)
{
	if (key_code == ESC)
		exit_game(data);
	if (key_code == W)
		forward(data, data->rc);
	else if (key_code == S)
		backward(data, data->rc);
	else if (key_code == D)
		right(data->rc);
	else if (key_code == A)
		left(data->rc);
	return (0);
}
