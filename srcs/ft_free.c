/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:57:19 by bvictoir          #+#    #+#             */
/*   Updated: 2025/06/09 11:46:51 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_int_array(t_texture *text)
{
	int	i;

	i = 0;
	while (i < 4)
		free(text->height[i++]);
	i = 0;
	while (i < 4)
		free(text->width[i++]);
}

void	free_text(t_texture *text, t_data *data)
{
	if (text->img[NO])
		mlx_destroy_image(data->mlx, text->img[NO]);
	if (text->img[SO])
		mlx_destroy_image(data->mlx, text->img[SO]);
	if (text->img[EA])
		mlx_destroy_image(data->mlx, text->img[EA]);
	if (text->img[WE])
		mlx_destroy_image(data->mlx, text->img[WE]);
	if (text->path[NO])
		free(text->path[NO]);
	if (text->path[SO])
		free(text->path[SO]);
	if (text->path[EA])
		free(text->path[EA]);
	if (text->path[WE])
		free(text->path[WE]);
	free_int_array(text);
	free(text);
}

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	exit_error(t_data *data, char *mess)
{
	if (data)
	{
		if (data->text)
			free_text(data->text, data);
		if (data->image)
		{	
			if (data->image->img)
				mlx_destroy_image(data->mlx, data->image->img);
			free(data->image);
		}
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
		if (data->rc)
			free(data->rc);
		if (data->map)
			free_map(data->map);
		free(data);
	}
	ft_printf(2, "error : %s\n", mess);
	exit(1);
}

int	exit_game(t_data *data)
{
	free_text(data->text, data);
	free_map(data->map);
	if (data->image->img)
		mlx_destroy_image(data->mlx, data->image->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->rc);
	free(data->image);
	free(data);
	exit(0);
	return (0);
}
