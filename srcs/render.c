/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:03:36 by gael              #+#    #+#             */
/*   Updated: 2025/06/05 15:31:35 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling_floor(t_raycast *rc, t_texture *text, t_image *img, int x)
{
	int	y;
	int	small_bpp;
	int	test;

	y = 0;
	small_bpp = img->bpp / 8;
	test = x * small_bpp;
	while (y < rc->wall_start)
	{
		*(unsigned int *)(img->addr + (y * img->size_line + test))
			= text->ceiling;
		y++;
	}
	y = rc->wall_end;
	while (y < WIN_HEIGHT - 1)
	{
		*(unsigned int *)(img->addr + (y * img->size_line + test))
			= text->floor;
		y++;
	}
}

int	get_tex_x(t_data *data, t_raycast *rc, t_texture *text)
{
	double		wall_x;
	int			tex_x;
	t_direction	dir;

	dir = get_direction(rc);
	if (rc->side == 0)
		wall_x = data->p_pos.y + rc->ray_dist * rc->ray_dir.y;
	else
		wall_x = data->p_pos.x + rc->ray_dist * rc->ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * *text->width[dir]);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= *text->width[dir])
		tex_x = *text->width[dir] - 1;
	return (tex_x);
}

void	draw_wall(t_data *data, t_raycast *rc, t_texture *text, int x)
{
	int			tex_x;
	double		step;
	double		tex_pos;
	int			y;
	t_image		tex_data;

	text->dir = get_direction(rc);
	tex_x = get_tex_x(data, rc, text);
	step = ((double)*text->height[text->dir] / rc->wall_height);
	tex_pos = (rc->wall_start - WIN_HEIGHT / 2 + rc->wall_height / 2) * step;
	y = rc->wall_start;
	tex_data.addr = mlx_get_data_addr(text->img[text->dir], &tex_data.bpp,
			&tex_data.size_line, &tex_data.endian);
	while (y < rc->wall_end)
	{
		tex_pos += step;
		*(unsigned int *)(data->image->addr + (y * data->image->size_line
					+ x * (data->image->bpp / 8)))
			= *(unsigned int *)(tex_data.addr + (get_tex_y(tex_pos, text)
					* tex_data.size_line + tex_x * (tex_data.bpp / 8)));
		y++;
	}
}
