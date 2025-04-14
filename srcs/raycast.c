/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:25:32 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/09 15:07:48 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_stripe(double ray_dist)//send line start and end somewhere
{
	int	line_height;
	int	line_start;
	int	line_end;

	line_height = (int)(WIN_HEIGHT / ray_dist);//is fisheye correction ok?
	line_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (line_start < 0)
		line_start = 0;
	line_end = line_height / 2 + WIN_HEIGHT / 2;
	if (line_end < 0)
		line_end = WIN_HEIGHT - 1;
}

double	get_wall_dist(t_raycast *rc, int side)
{
	double	wall_dist;

	if (side == 0)
		wall_dist = (rc->side_d.x - rc->delta_d.x);
	else
		wall_dist = (rc->side_d.y - rc->delta_d.y);
	return (wall_dist);
}

double	dda(t_data *data, t_raycast *rc)
{
	int	side;
	int	map_x;
	int	map_y;

	map_x = (int)rc->p_pos.x;
	map_y = (int)rc->p_pos.y;
	while (1)
	{
		if (rc->side_d.x < rc->side_d.y)
		{
			rc->side_d.x += rc->delta_d.x;
			map_x += rc->step_x;
			side = 0;
		}
		else
		{
			rc->side_d.y += rc->delta_d.y;
			map_y += rc->step_y;
			side = 1;
		}
		if (data->config->map[map_x][map_y] == '1')//check if right x y order
			break;
	}
	return (get_wall_dist(rc, side));
}

void	init_rc(t_data *data, t_raycast *rc)
{
	rc->delta_d.x = fabs(1 / rc->ray_dir.x);
	rc->delta_d.y = fabs(1 / rc->ray_dir.y);
	if (rc->ray_dir.x < 0)
	{
		rc->step_x = -1;
		rc->side_d.x = (rc->p_pos.x - (int)rc->p_pos.x) * rc->delta_d.x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_d.x = ((int)rc->p_pos.x + 1.0 - rc->p_pos.x) * rc->delta_d.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step_y = -1;
		rc->side_d.y = (rc->p_pos.y - (int)rc->p_pos.y) * rc->delta_d.y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_d.y = ((int)rc->p_pos.y + 1.0 - rc->p_pos.y) * rc->delta_d.y;
	}
}

void	ray_cast(t_data *data)//init rc/player_dir first
{
	int	x;
	double	cam_x;
	double	ray_dist;
	t_raycast	*rc;

	x = 0;
	rc = malloc(sizeof(t_raycast));
	if (!rc)//free/print error
		exit(1);
	init_player_dir(data, rc, data->p_pos_x, data->p_pos_y);
	while(x < WIN_WIDTH)
	{
		cam_x = 2 * x / (double)WIN_WIDTH - 1;
		rc->ray_dir.x = rc->p_dir.x + rc->plane.x * cam_x;
		rc->ray_dir.y = rc->p_dir.y + rc->plane.x * cam_x;
		init_rc(data, rc);//bad name
		ray_dist = dda(data, rc);
		draw_stripe(ray_dist);//refactor with mlx/ maybe add line start and end to rc struct
		x++;
	}
}