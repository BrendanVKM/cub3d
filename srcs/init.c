/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:26:44 by bvictoir          #+#    #+#             */
/*   Updated: 2025/06/11 14:44:38 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(t_data *data, t_raycast *ray, double cam_x)
{
	ray->map_x = (int)data->p_pos.x;
	ray->map_y = (int)data->p_pos.y;
	ray->ray_dir.x = ray->p_dir.x + ray->plane.x * cam_x;
	ray->ray_dir.y = ray->p_dir.y + ray->plane.y * cam_x;
}

static void	init_vector(t_vec *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
}

static void	init_int_array(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->text->width[i] = malloc(sizeof(int));
		if (!data->text->width[i])
			exit_error(data, "Malloc failed");
		*(data->text->width[i]) = 0;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		data->text->height[i] = malloc(sizeof(int));
		if (!data->text->height[i])
			exit_error(data, "Malloc failed");
		*(data->text->height[i]) = 0;
		i++;
	}
}

void	init_player_dir(t_data *data, t_raycast *rc)
{
	double	plane_len;
	double	fov_rad;

	fov_rad = FOV * M_PI / 180.0;
	plane_len = tan(fov_rad / 2.0);
	if (data->orientation == NO)
		init_vector(&rc->p_dir, 0.0f, -1.0f);
	if (data->orientation == SO)
		init_vector(&rc->p_dir, 0.0f, 1.0f);
	if (data->orientation == EA)
		init_vector(&rc->p_dir, 1.0f, 0.0f);
	if (data->orientation == WE)
		init_vector(&rc->p_dir, -1.0f, 0.0f);
	rc->plane.x = -rc->p_dir.y * plane_len;
	rc->plane.y = rc->p_dir.x * plane_len;
	init_int_array(data);
}

void	init(t_data *data)
{
	int	i;

	if (!data)
		exit_data_p(data, "Error: Data malloc fail");
	data->map = NULL;
	data->tmp_line = NULL;
	data->p_pos.x = -1;
	data->p_pos.y = -1;
	data->orientation = '\0';
	data->text = malloc(sizeof(t_texture));
	if (!data->text)
		exit_data_p(data, "Error: Text malloc fail");

	i = 0;
	while (i < 4)
		data->text->path[i++] = NULL;
	data->text->ceiling_rgb = NULL;
	data->text->floor_rgb = NULL;
}
