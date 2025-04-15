/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:25:32 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/15 15:10:28 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_height(t_data *data, t_raycast *rc, double ray_dist)
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
			rc->side = 0;
		}
		else
		{
			rc->side_d.y += rc->delta_d.y;
			map_y += rc->step_y;
			rc->side = 1;
		}
		if (data->config->map[map_x][map_y] == '1')//check if right x y order
			break;
	}
	return (get_wall_dist(rc));
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
	ft_memset(rc, 0, sizeof(t_raycast));
	init_player_dir(data, rc, data->p_pos_x, data->p_pos_y);
	while(x < WIN_WIDTH)
	{
		cam_x = 2 * x / (double)WIN_WIDTH - 1;
		rc->ray_dir.x = rc->p_dir.x + rc->plane.x * cam_x;
		rc->ray_dir.y = rc->p_dir.y + rc->plane.x * cam_x;
		init_rc(data, rc);//bad name
		ray_dist = dda(data, rc);
		get_wall_height(data, rc, ray_dist);
		texture_rendering(data, rc, ray_dist, x);
		x++;
	}
}