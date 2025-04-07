/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:39:16 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/07 17:26:56 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//step has to be int

double	get_step(t_vec *ray_dir, char c)
{
	double	step;

	if (c == 'x')
	{
		if (ray_dir->x < 0)
			step = -1;
		else
			step = 1;
	}
	else
	{
		if (ray_dir->y < 0)
			step = -1;
		else
			step = 1;
	}
	return (step);
}

double	dda(t_data *data, t_vec *side_dist, t_vec delta_dist, t_vec step)
{
	int	side;
	int	map_x;
	int	map_y;
	double	wall_dist;

	map_x = (int)data->player->pos_x;
	map_y = (int)data->player->pos_y;
	while (1)
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += delta_dist.x;
			map_x += (int)step.y;
			side = 0;
		}
		else
		{
			side_dist->y += delta_dist.y;
			map_y += (int)step.y;
			side = 1;
		}
		if (data->config->map[map_y][map_x] == '1')//check if order x y is good
			break;
	}
	wall_dist = measure_wall(data, idk);
}

double	get_dist(t_data *data, t_player *player)
{
	t_vec	delta_dist;
	t_vec	step;
	t_vec	side_dist;

	delta_dist.x = fabs(1 / player->ray_dir.x);
	delta_dist.y = fabs(1 / player->ray_dir.y);
	step.x = get_step(&player->ray_dir, 'x');
	step.y = get_step(&player->ray_dir, 'y');
	if (player->ray_dir.x < 0)
		side_dist.x = (player->pos_x - (int)player->pos_x) * delta_dist.x;
	else
		side_dist.x = ((int)player->pos_x + 1.0 - player->pos_x) * delta_dist.x;
	if (player->ray_dir.y < 0)
		side_dist.y = (player->pos_y - (int)player->pos_y) * delta_dist.y;
	else
		side_dist.y = ((int)player->pos_y + 1.0 - player->pos_y) * delta_dist.y;
	return (dda(data, &side_dist, delta_dist, step));
}

void	ray_cast(t_data *data, t_player *player)//init player dir at beginning of game
{
	int	x;
	double	cam_x;
	double	ray_dist;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cam_x = 2 * x / (double)WIN_WIDTH- 1;
		player->ray_dir.x = player->p_dir.x + player->plane.x * cam_x;
		player->ray_dir.y = player->p_dir.y + player->plane.y * cam_x;
		ray_dist = get_dist(data, player);
	}
}