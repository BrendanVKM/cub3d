/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:33:29 by lemarian          #+#    #+#             */
/*   Updated: 2025/05/15 13:32:50 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vector(t_vec *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
}

void	init_player_dir(t_data *data, t_raycast *rc)//use enum or char?
{
	if (data->orientation == NO)
	{	
		init_vector(&rc->p_dir, 0.0f, -1.0f);//jean uses opposite values??
		init_vector(&rc->plane, 0.0f, tan(FOV / 2));
	}
	if (data->orientation == SO)
	{
		init_vector(&rc->p_dir, 0.0f, 1.0f);
		init_vector(&rc->plane, 0.0f, -tan(FOV / 2));
	}
	if (data->orientation == EA)
	{
		init_vector(&rc->p_dir, 1.0f, 0.0f);
		init_vector(&rc->plane, tan(FOV /2), 0.0f);
	}
	if (data->orientation == WE)
	{
		init_vector(&rc->p_dir, -1.0f, 0.0f);
		init_vector(&rc->plane, -tan(FOV /2), 0.0f);
	}
}

void	init(t_data *data)
{
	if (!data)
		exit(ft_printf(2, "Error: Malloc fail\n"));
	data->text = malloc(sizeof(t_texture));
	if (!data->text)
		exit(ft_printf(2, "Error: Malloc fail\n"));
	data->text->ceiling_rgb = NULL;
	data->text->floor_rgb = NULL;
	data->map = NULL;
	ft_memset(data->text->path, '\0', sizeof(char) * 4);
	ft_memset(data->text->height, 0, sizeof(data->text->height));//not sure about this
	ft_memset(data->text->width, 0, sizeof(data->text->width));
}
