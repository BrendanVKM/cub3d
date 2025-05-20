/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:18:25 by lemarian          #+#    #+#             */
/*   Updated: 2025/05/20 11:25:53 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_ceiling(t_data *data, t_raycast *rc, t_texture *text, int x)
{
	int	y;

	y = 0;
	while (y < rc->wall_start)
	{
		data->buffer[y * WIN_WIDTH + x] = text->ceiling;
		y++;
	}
}

void	render_floor(t_data *data, t_raycast *rc, t_texture *text, int x)
{
	int	y;

	y = rc->wall_end;
	while (y < WIN_HEIGHT)
	{
		data->buffer[y * WIN_WIDTH + x] = text->ceiling;
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

void	rendering(t_data *data, t_raycast *rc, t_texture *text, int x)
{
	int	y;
	int	tex_y;
	int	tex_x;
	double	tex_pos;
	double	step;
	int	tex_height;
	int	tex_num; 
	uint32_t	color;

	tex_num = data->map[rc->map_x][rc->map_y] - 1;
	tex_x = get_tex_x(data, rc, data->text);
	tex_height = *text->height[get_direction(rc)];
	step = 1.0 * tex_height / rc->wall_height;
	tex_pos = (rc->wall_start - WIN_HEIGHT / 2 + rc->wall_height) * step;
	render_ceiling(data, rc, text, x);
	y = rc->wall_start;
	while (y < rc->wall_end)
	{
		tex_y = (int)tex_pos & (tex_height - 1);
		tex_pos += step;
		color = text->addr[tex_num][tex_height * tex_y + tex_x];
		data->buffer[y * WIN_WIDTH + x] = color;
		y++;
	}
	render_floor(data, rc, text, x);
}