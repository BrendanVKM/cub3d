/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:28:14 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/01 17:23:27 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main()
{
	double pos_x; // player position
	double pos_y;
	double dir_x = -1; // initial direction vector, left-most part of screen
	double dir_y = 0; // aim for back of the map?
	double plane_x = 0;
	double plane_y = 0.66; // "2d raycaster version" of camera plane? 0.66 = fov of 66 degrees

	while (!done())
	{
		double ray_dir_x;
		double ray_dir_y;
		double delta_dist_x = fabs(1 / ray_dir_x);// distance from one x line to next x line
		double delta_dist_y = fabs(1 / ray_dir_y);//needed to calculate ratio between delta_dist_x and delta_dist_y
		double perpWallDist;// used to calculate length of ray
		int hit = 0;
		int side; //ray hit x-side (0) or y-side (1), determines orientation of wall that was hit (NS or EW)
		
		for (int x = 0; x < WIN_WIDTH; x++)//parcours axe x ->
		{
			double camera_x = 2 * x / (double)WIN_WIDTH - 1;// position of x in camera space, right side of screen = 1, center = 0, left = -1
			ray_dir_x = dir_x + plane_x * camera_x; // sum of direction vector and part of the camera plane
			ray_dir_y = dir_y + plane_y * camera_x;
		}
		int map_x = (int)pos_x;// coordinates of current square the ray is in
		int map_y = (int)pos_y;

		double side_dist_x;// distance from start ray start position to first x line, later incremented each step
		double side_dist_y;// distance from start ray start position to first y line
		int step_x;// either 1 or -1, determines if we go in positive or negative x and y direction
		int step_y;// depends on if ray_dir_y is positive or negative(same for step_x)
		
		if (ray_dir_x < 0)// side dist is distance from ray starting position to first x line on the left
		{
			step_x = -1;
			side_dist_x = (pos_x - map_x) * delta_dist_x; // subtract int version of pos to real position
		}
		else //
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0) // side dist is distance from ray starting position to first y line above or below
		{
			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
		}
	}
}