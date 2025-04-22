/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:33:29 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/22 15:17:27 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vector(t_vec *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
}

void	init_player_dir(t_data *data, t_raycast *rc, int x, int y)
{
	//x and y are player start coordinnates
	if (data->map[y][x] == 'N')
	{	
		init_vector(&rc->p_dir, 0.0f, -1.0f);//jean uses opposite values??
		init_vector(&rc->plane, 0.0f, tan(FOV / 2));
	}
	if (data->map[y][x] == 'S')
	{
		init_vector(&rc->p_dir, 0.0f, 1.0f);
		init_vector(&rc->plane, 0.0f, -tan(FOV / 2));
	}
	if (data->map[y][x] == 'E')
	{
		init_vector(&rc->p_dir, 1.0f, 0.0f);
		init_vector(&rc->plane, tan(FOV /2), 0.0f);
	}
	if (data->map[y][x] == 'W')
	{
		init_vector(&rc->p_dir, -1.0f, 0.0f);
		init_vector(&rc->plane, -tan(FOV /2), 0.0f);
	}
}