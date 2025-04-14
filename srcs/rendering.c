/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:21:23 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/14 15:25:12 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tex_stretch(t_data *data, t_raycast *rc)
{
	double	step; // interval between pixels depending on line height
	double	tex_pos;
	int	y;
	int	tex_y;
	uint32_t	color; // research this

	y = rc->wall_start;
	step = 1.0 * tex_height / rc->wall_height;
	tex_pos = (rc->wall_start - WIN_HEIGHT / 2 + rc->wall_height / 2) * step;
	while (y < rc->wall_end)
	{
		tex_y = (int)tex_pos & (tex_height - 1);
		tex_pos += step;
		color = texture[tex_height * tex_y + tex_y]; // use texture address?
		if (rc->side == 1)
			color = (color >> 1) & 83355711;
		buffer[y][x] = color; // ?
		y++;
	}
}

void	texture_rendering(t_data *data, t_raycast *rc, double ray_dist)
{
	double	wall_x; //point where ray hits wall
	int		tex_x;

	if (rc->side == 0)
		wall_x = rc->p_pos.y + ray_dist * rc->ray_dir.y; // hits x side
	else
		wall_x = rc->p_pos.x + ray_dist * rc->ray_dir.x; // hits y side
	wall_x -= floor(wall_x); //removes integreal part of value, only keep float (between 0 and 1)
	tex_x = (int)(wall_x * (double)tex_width); // need to store texture size somewhere
	if (rc->side == 0 && rc->ray_dir.x > 0) // texture is handled differently depending on direction
		tex_x = tex_witdh - tex_x - 1; // x axis (south)
	if (rc->side == 1 && rc->ray_dir.y < 0)
		tex_x = text_width - tex_x - 1;	// y axis (west)

}