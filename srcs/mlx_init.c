/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:33:18 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/24 15:58:13 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_init(void *mlx, t_texture *text)//not protected
{
	int	bpp;
	int	endian;
	int size;

	text->img[NO] = mlx_xpm_file_to_image(mlx, text->path[NO], text->width[NO], text->height[NO]);
	text->img[SO] = mlx_xpm_file_to_image(mlx, text->path[SO], text->width[SO], text->height[SO]);
	text->img[EA] = mlx_xpm_file_to_image(mlx, text->path[EA], text->width[EA], text->height[EA]);
	text->img[WE] = mlx_xpm_file_to_image(mlx, text->path[WE], text->width[WE], text->height[WE]);
	text->addr[NO] = mlx_get_data_addr(text->img[NO], &bpp, &size, &endian);
	text->addr[SO] = mlx_get_data_addr(text->img[SO], &bpp, &size, &endian);
	text->addr[EA] = mlx_get_data_addr(text->img[EA], &bpp, &size, &endian);
	text->addr[WE] = mlx_get_data_addr(text->img[WE], &bpp, &size, &endian);
	return (1);
}

int	set_up_mlx(t_data *data, t_texture *text)//not protected at all
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub");
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->buffer = (int*)data->img;
	texture_init(data, text);
	return (1);
}