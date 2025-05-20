/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:51:15 by lemarian          #+#    #+#             */
/*   Updated: 2025/05/20 15:23:52 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdint.h>
#include <inttypes.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, uint32_t color)
{
	char	*dst;
	char	*addr;
	int	bpp;
	int	endian;
	int	size_line;

	addr = mlx_get_data_addr(data->img, &bpp, &size_line, &endian);
	dst = addr + (y * size_line + x * (bpp / 8));
	*(unsigned int *)dst = color;
}



void	rendering(t_data *data, t_raycast *rc, t_texture *text, int x)
{
	int	y;

	printf("floor %" PRIu32 "\n", text->floor);
	printf("ceiling %" PRIu32 "\n", text->ceiling);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		if (y < (WIN_HEIGHT - rc->wall_height) / 2)
			my_mlx_pixel_put(data, x, y, data->text->ceiling);
		else if (y > (WIN_HEIGHT + rc->wall_height) / 2)
			my_mlx_pixel_put(data, x, y, data->text->floor);
		else
			render_wall(data, rc, text, x);
	}
}