/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:06:41 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/14 16:48:33 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//trying to rework raycasting with textures using lodev tutorial

void	ray_cast(t_data *data)
{
	int	x;
	double	cam_x;
	double	ray_dist;
	t_raycast	*rc;
	uint32_t	buff[WIN_HEIGHT][WIN_WIDTH];
	uint32_t	tex[TEX_HEIGHT][TEX_WIDTH];

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
		texture_rendering(data, rc, ray_dist);
		x++;
	}
}