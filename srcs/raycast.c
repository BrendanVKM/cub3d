/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:35:53 by lemarian          #+#    #+#             */
/*   Updated: 2025/06/03 14:32:31 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_height(t_raycast *rc, double ray_dist)
{
	double	raw_start;
	double	raw_end;
	double	raw_height;
	
	raw_height = ((double)WIN_HEIGHT / ray_dist);
	rc->wall_height = (int)raw_height;
	raw_start =  (WIN_HEIGHT - raw_height) / 2.0;
	rc->wall_start = (int)ceil(raw_start);
	if (rc->wall_start < 0)
		rc->wall_start = 0;
	raw_end = raw_start + raw_height;
	rc->wall_end = (int)floor(raw_end);
	if (rc->wall_end >= WIN_HEIGHT)
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
	while (data->map[rc->map_y][rc->map_x] != '1')
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
	}
	return (get_wall_dist(rc));
}

void	start_raycast(t_data *data, t_raycast *rc)
{
	rc->delta_d.x = sqrt(1 + (rc->ray_dir.y * rc->ray_dir.y) / (rc->ray_dir.x * rc->ray_dir.x)); // old : fabs(1 / rc->ray_dir.x);
	rc->delta_d.y = sqrt(1 + (rc->ray_dir.x * rc->ray_dir.x) / (rc->ray_dir.y * rc->ray_dir.y));
	if (rc->ray_dir.x < 0)
	{
		rc->step_x = -1;
		rc->side_d.x = (data->p_pos.x - rc->map_x) * rc->delta_d.x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_d.x = (rc->map_x + 1.0 - data->p_pos.x) * rc->delta_d.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step_y = -1;
		rc->side_d.y = (data->p_pos.y - rc->map_y) * rc->delta_d.y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_d.y = (rc->map_y + 1.0 - data->p_pos.y) * rc->delta_d.y;
	}
}

int	raycast(t_data *data)
{
	int			x;
	double		cam_x;
	t_raycast	*ray;
	double		raw_dist;
	double		angle_diff;

	x = 0;
	ray = data->rc;
	mlx_clear_window(data->mlx, data->win);
	while (x < WIN_WIDTH)
	{
		cam_x = 2 * x / (double)WIN_WIDTH - 1;
		ray->map_x = (int)data->p_pos.x;
		ray->map_y = (int)data->p_pos.y;
		ray->ray_dir.x = ray->p_dir.x + ray->plane.x * cam_x;
		ray->ray_dir.y = ray->p_dir.y + ray->plane.y * cam_x;
		start_raycast(data, data->rc);
		raw_dist = dda(data, data->rc);
		angle_diff = atan2(ray->ray_dir.y, ray->ray_dir.x) - atan2(ray->p_dir.y, ray->p_dir.x);
		ray->ray_dist = raw_dist * cos(angle_diff);
		if (ray->ray_dist < 0.01)
			ray->ray_dist = 0.01;
		get_wall_height(data->rc, ray->ray_dist);
		draw_wall(data, data->rc, data->text, x);
		draw_ceiling_floor(data->rc, data->text, data->image, x);
		x++;
	}
	return (0);
}