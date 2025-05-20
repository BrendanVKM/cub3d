/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:30:55 by lemarian          #+#    #+#             */
/*   Updated: 2025/05/20 11:25:41 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_height(t_raycast *rc, double ray_dist)
{
	rc->wall_height = (int)(WIN_HEIGHT / ray_dist);
	rc->wall_start = -rc->wall_height / 2 + WIN_HEIGHT / 2;
	if (rc->wall_start < 0)
		rc->wall_start = 0;
	rc->wall_end = rc->wall_height / 2 + WIN_HEIGHT / 2;
	if (rc->wall_end < 0)
		rc->wall_end = WIN_HEIGHT - 1;
}


double	get_wall_dist(t_raycast *rc)
{
	double	wall_dist;

	if (rc->side == 0)
		wall_dist = (rc->side_d.x - rc->delta_d.x);
	else
		wall_dist = (rc->side_d.y - rc->delta_d.y);
	return (wall_dist);
}

double	dda(t_data *data, t_raycast *rc)
{
	rc->map_x = (int)data->p_pos.x;
	rc->map_y = (int)data->p_pos.y;
	while (1)
	{
		if (rc->side_d.x < rc->side_d.y)
		{
			rc->side_d.x += rc->delta_d.x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_d.y += rc->delta_d.y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (data->map[rc->map_x][rc->map_y] == '1')//check if right x y order
			break;
	}
	return (get_wall_dist(rc));
}

void	start_raycast(t_data *data, t_raycast *rc)
{
	rc->delta_d.x = fabs(1 / rc->ray_dir.x);
	rc->delta_d.y = fabs(1 / rc->ray_dir.y);
	if (rc->ray_dir.x < 0)
	{
		rc->step_x = -1;
		rc->side_d.x = (data->p_pos.x - (int)data->p_pos.x) * rc->delta_d.x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_d.x = ((int)data->p_pos.x + 1.0 - data->p_pos.x) * rc->delta_d.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step_y = -1;
		rc->side_d.y = (data->p_pos.y - (int)data->p_pos.y) * rc->delta_d.y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_d.y = ((int)data->p_pos.y + 1.0 - data->p_pos.y) * rc->delta_d.y;
	}
}

int	raycast(t_data *data)
{
	int	x;
	double	cam_x;
	double	ray_dist;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cam_x = 2 * x / (double)WIN_WIDTH - 1;
		data->rc->ray_dir.x = data->rc->p_dir.x + data->rc->plane.x * cam_x;
		data->rc->ray_dir.y = data->rc->p_dir.y + data->rc->plane.x * cam_x;
		start_raycast(data, data->rc);
		ray_dist = dda(data, data->rc);
		get_wall_height(data->rc, ray_dist);
		rendering(data, data->rc, data->text, x);
		x++;
	}
	return (0);
}
