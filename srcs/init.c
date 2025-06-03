/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:33:29 by lemarian          #+#    #+#             */
/*   Updated: 2025/06/03 11:21:22 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{	
		init_vector(&rc->p_dir, 0.0f, -1.0f);
		rc->plane.x = rc->p_dir.y * plane_len;
		rc->plane.y = -rc->p_dir.x * plane_len;
	}
	if (data->orientation == SO)
	{
		init_vector(&rc->p_dir, 0.0f, 1.0f);
		rc->plane.x = rc->p_dir.y * plane_len;
		rc->plane.y = -rc->p_dir.x * plane_len;
	}
	if (data->orientation == EA)
	{
		init_vector(&rc->p_dir, 1.0f, 0.0f);
		rc->plane.x = rc->p_dir.y * plane_len;
		rc->plane.y = -rc->p_dir.x * plane_len;
	}
	if (data->orientation == WE)
	{
		init_vector(&rc->p_dir, -1.0f, 0.0f);
		rc->plane.x = rc->p_dir.y * plane_len;
		rc->plane.y = -rc->p_dir.x * plane_len;
	}
	init_int_array(data);
}

void	init(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		exit_data_p(data, "Error: Data malloc fail\n");
	data->text = malloc(sizeof(t_texture));
	if (!data->text)
		exit_data_p(data, "Error: Text malloc fail\n");
	while (i < 4)
		data->text->path[i++] = NULL;
	data->text->ceiling_rgb = NULL;
	data->text->floor_rgb = NULL;
	data->map = NULL;
	data->tmp_line = NULL;
	data->p_pos.x = -1;
	data->p_pos.y = -1;
	data->orientation = '\0';
}
