/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:33:18 by lemarian          #+#    #+#             */
/*   Updated: 2025/05/20 11:24:24 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_init(void *mlx, t_texture *text, t_data *data)
{
	int	bpp;
	int	endian;
	int size;
	
	text->img[NO] = mlx_xpm_file_to_image(mlx, text->path[NO], text->width[NO], text->height[NO]);
	text->img[SO] = mlx_xpm_file_to_image(mlx, text->path[SO], text->width[SO], text->height[SO]);
	text->img[EA] = mlx_xpm_file_to_image(mlx, text->path[EA], text->width[EA], text->height[EA]);
	text->img[WE] = mlx_xpm_file_to_image(mlx, text->path[WE], text->width[WE], text->height[WE]);
	if (!text->img[NO] || !text->img[SO] || !text->img[EA] || !text->img[WE])
		exit_error(data, "failed to load textures");
	text->addr[NO] = mlx_get_data_addr(text->img[NO], &bpp, &size, &endian);
	text->addr[SO] = mlx_get_data_addr(text->img[SO], &bpp, &size, &endian);
	text->addr[EA] = mlx_get_data_addr(text->img[EA], &bpp, &size, &endian);
	text->addr[WE] = mlx_get_data_addr(text->img[WE], &bpp, &size, &endian);
}

int	set_up_mlx(t_data *data, t_texture *text)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error(data, "failed to initialize mlx");
	texture_init(data->mlx, text, data);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	if (!data->win)
		exit_error(data, "failed to create window");
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		exit_error(data, "failed to create image display");
	data->buffer = (int *)data->img;
	texture_init(data->mlx, text, data);
	return (1);
}