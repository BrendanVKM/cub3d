/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:19:12 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/15 14:41:39 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vector(t_vec *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
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

void	init_player_dir(t_data *data, t_raycast *rc, int x, int y)// init before raycast game loop
{
	//x and y are player start coordinnates
	if (data->config->map[y][x] == 'N')
	{	
		init_vector(&rc->p_dir, 0.0f, -1.0f);//jean uses opposite values??
		init_vector(&rc->plane, 0.0f, tan(FOV / 2));//for some reason y is inverted with cam compared to player dir...
	}
	if (data->config->map[y][x] == 'S')
	{
		init_vector(&rc->p_dir, 0.0f, 1.0f);
		init_vector(&rc->plane, 0.0f, -tan(FOV / 2));
	}
	if (data->config->map[y][x] == 'E')
	{
		init_vector(&rc->p_dir, 1.0f, 0.0f);
		init_vector(&rc->plane, tan(FOV /2), 0.0f);
	}
	if (data->config->map[y][x] == 'W')
	{
		init_vector(&rc->p_dir, -1.0f, 0.0f);
		init_vector(&rc->plane, -tan(FOV /2), 0.0f);
	}
}