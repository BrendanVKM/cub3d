/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:19:12 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/07 15:20:33 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vector(t_vec *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
}

void	init_player_dir(t_data *data, int x, int y)// init before raycast game loop
{
	//x and y are player start coordinnates
	if (data->config->map[y][x] == 'N')
	{	
		init_vector(&data->player->p_dir, 0.0f, -1.0f);//jean uses opposite values??
		init_vector(&data->player->plane, 0.0f, tan(FOV / 2));//for some reason y is inverted with cam compared to player dir...
	}
	if (data->config->map[y][x] == 'S')
	{
		init_vector(&data->player->p_dir, 0.0f, 1.0f);
		init_vector(&data->player->plane, 0.0f, -tan(FOV / 2));
	}
	if (data->config->map[y][x] == 'E')
	{
		init_vector(&data->player->p_dir, 1.0f, 0.0f);
		init_vector(&data->player->plane, tan(FOV /2), 0.0f);
	}
	if (data->config->map[y][x] == 'W')
	{
		init_vector(&data->player->p_dir, -1.0f, 0.0f);
		init_vector(&data->player->plane, -tan(FOV /2), 0.0f);
	}
}