/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:18:25 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/22 15:39:02 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rendering(t_data *data, t_raycast *rc, double ray_dist, int x)//rework, need texture info
{
	int	tex_num;
	double	wall_x;

	tex_num = data->map[rc->map_x][rc->map_y] - 1;
	if (rc->side == 0)
		wall_x = rc->p_pos.y + ray_dist * rc->ray_dir.y;
	else
		wall_x = rc->p_pos.x + ray_dist * rc->ray_dir.x;
	wall_x = -floor(wall_x);
}