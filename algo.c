/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:11:06 by lemarian          #+#    #+#             */
/*   Updated: 2025/03/31 17:12:49 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//x <->
//source = reactive article
int main(void)
{
	//calculate direction of the ray
	int x = 0;
	while (x < WIN_WIDTH)
	{
		double camera_x = 2 * x / (double)WIN_WIDTH - 1;//camera plane vector, perpendicular to direction vector, represents screen
		double ray_dir_x = dir_x + plane_x * camera_x;//camera_x = x-coordonate of the ray in camera space
		double ray_dir_y = dir_y + plane_y * camera_x; // dir = orientation of player, what is player plane? difference with camera plane?
	}

	//calculate delta distance to next intersection of ray with x and y grid lines
	int map_x = (int)pos_x; //player position
	int map_y = (int)pos_y; //player position
	double delta_dist_x = fabs(1 / ray_dir_x);//fabs() = takes single (double) argument returns absolute value of that number in (double)
	double delta_dist_y = fabos(1 / ray_dir_y);

	//calculate step and initial distance
	int step_x; // direction in which ray moves through the grid
	int step_y;
	double side_dist_x; // distance from ray to next grid line, later updated to delta distance
	double side_dist_y;

	if (ray_dir_x < 0)//par rapport au camera plane?
	{
		step_x = -1;
		side_dist_x = (pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
	}

	//DDA
	int side;

	while (42)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x; //update map position of ray
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1; // ?
		}
		if (map[map_x][map_y] == '1')
			break; // check if ray hit wall
	}

	// calculate wall height
	double wall_dist;

	if (side == 0)
		wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
	else
		wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;

	int line_height = (int)(WIN_HEIGHT / wall_dist);

	int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;

	if (side == 0)
		wall_x = pos_y + wall_dist * ray->dy;
	else
		wall_x = pos_x + wall_dist * ray->sx;
	wal_x -= floor(wall_x); // rounds number down to nearest integer
}