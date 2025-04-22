/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:42:54 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/22 15:20:58 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
- init img with mlx
- use raycasting to get wall height
- get texture colors to insert in image
- fill floor + ceiling with color in img
- print img to screen
*/

void	rendering(t_data *data, t_raycast *rc, double ray_dist, int x)
{
	int		tex_num;// value of current map square
	double	wall_x; // value where wall was hit by ray
	int		tex_x; // x coordinate of texture
	int		tex_y;
	double	step;
	double	tex_pos;
	uint32_t	color;
	int		y;

	tex_num = data->map[rc->map_x][rc->map_y] - 1;
	if (rc->side == 0)
		wall_x = rc->p_pos.y + ray_dist * rc->ray_dir.y;
	else
		wall_x = rc->p_pos.x + ray_dist * rc->ray_dir.x;
	wall_x = -floor(wall_x);
	tex_x = (int)(wall_x * (double)(tex_width));
	if (rc->side == 0 && rc->ray_dir.x > 0)
		tex_x = tex_width - tex_x - 1;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		tex_x = tex_width - tex_x - 1;
	//now need y coordinate of texture to draw stripe of wall
	step = 1.0 * tex_height / rc->wall_height;
	tex_pos = (rc->wall_start - WIN_HEIGHT / 2 + rc->wall_height) * step;
	y = rc->wall_start;
	while (y < rc->wall_end)
	{
		tex_y = (int)tex_pos & (tex_height - 1);
		tex_pos += step;
		color = texture[tex_num][tex_height * tex_y + tex_x];
		data->img[y][x]; //need to calculate proper pixel position
		y++;
	}
}