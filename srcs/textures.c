/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:55:52 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/15 17:20:59 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_image(t_data *data)
{
	void	*img;
	int		bpp; //number of bits per pixel (char = 8 bits * 4 = 32)
	int		size_line; //size of a line/screen width * 4 (bc 1 pixel = 4 char)
	int		endian;// 0 or 1 depending on computer architecture
	char	*img_data;

	img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);// now can navigate img pixel by pixel instead of having to jump 4 each time
	img_data[current_height * WIN_WIDTH + current_width] = 0xFFFFFF; // this is not 2d array, can't use x and y to find pixel position
	mlx_put_image_to_window(data->mlx, data->win, img, 0, 0); // print image to screen
}