/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:25:48 by lemarian          #+#    #+#             */
/*   Updated: 2025/05/22 19:28:59 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling_floor(t_raycast *rc, t_texture *text, t_image *image, int x)
{
	int	y;

	y = 0;
	while (y < rc->wall_start)
	{
		*(unsigned int *)(image->addr + (y * image->size_line + x * (image->bpp / 8))) = text->ceiling;
		y++;
	}
	y = rc->wall_end;
	while (y < WIN_HEIGHT)
	{
		*(unsigned int *)(image->addr + (y * image->size_line + x * (image->bpp / 8))) = text->floor;
		y++;
	}
}

int	get_direction(t_raycast *rc)
{
	if (rc->side == 0)
	{
		if (rc->ray_dir.x < 0)
			return (NO);
		else
			return (SO);
	}
	else
	{
		if (rc->ray_dir.y < 0)
			return (EA);
		else
			return (WE);
	}
}

double	get_wall_x(t_data *data, t_raycast *rc)
{
	double	wall_x;

	if (rc->side == 0)
		wall_x = data->p_pos.y + rc->ray_dist * rc->ray_dir.y;
	else
		wall_x = data->p_pos.x + rc->ray_dist * rc->ray_dir.x;
	wall_x = -floor(wall_x);
	return (wall_x);
}

int	get_tex_x(t_data *data, t_raycast *rc, t_texture *texts)
{
	double	wall_x;
	int	tex_width;
	int	tex_x;
	int	dir;

	dir = get_direction(rc);
	tex_width = *texts->width[dir];
	wall_x = get_wall_x(data, rc);
	tex_x = (int)(wall_x * (double)(tex_width));
	if (rc->side == 0 && rc->ray_dir.x > 0)
		tex_x = tex_width - tex_x - 1;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

void	draw_wall(t_data *data, t_raycast *rc, t_texture *text, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		tex_x;
	t_direction	dir;
	t_image	tex_data;
	double	wall_x;

	dir = data->orientation;
	tex_x = get_tex_x(data, rc, text);
	wall_x = get_wall_x(data, rc);
	step = ((double)*text->height[dir] / rc->wall_height);
	tex_pos = (rc->wall_start - WIN_HEIGHT / 2 + rc->wall_height / 2) * step;
	y = rc->wall_start;
	mlx_get_data_addr(text->img[dir], &tex_data.bpp, &tex_data.size_line, &tex_data.endian);
	while (y < rc->wall_end)
	{
		tex_y = (int)tex_pos & (*text->height[dir] - 1);
		tex_pos += step;
		*(unsigned int *)(data->image->addr + (y * data->image->size_line + x * (data->image->bpp / 
			8))) = *(unsigned int *)(text->addr[dir] + (tex_y * - tex_data.size_line + tex_x * (tex_data.bpp / 8)));
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
}

/*void	render(t_data *data, t_raycast *rc, t_texture *text, int x)
{
	
}*/