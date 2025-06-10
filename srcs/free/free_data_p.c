/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:57:18 by bvictoir          #+#    #+#             */
/*   Updated: 2025/06/10 11:23:16 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	close_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
		close(fd++);
}

static void	free_texture(t_data *data)
{
	int	i;

	i = 0;
	if (!data->text)
		return ;
	while (i < 4)
	{
		if (data->text->path[i])
			free(data->text->path[i]);
		i++;
	}
	if (data->text)
		free(data->text);
}

void	rgb_error(t_data *data, int **rgb, char **split)
{
	if (split)
		ft_free_tab(&split);
	if (rgb && *rgb)
		free(*rgb);
	exit_data_p(data, "Error: Invalid RGB values");
}

void	free_end_p(t_data *data)
{
	close_fds();
	if (data->tmp_line)
		free(data->tmp_line);
}

void	exit_data_p(t_data *data, char *msg)
{
	if (!data)
	{
		write(2, "Error: ", 7);
		write(2, msg, ft_strlen(msg)); 
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	free_texture(data);
	if (data->map)
		ft_free_tab(&data->map);
	if (data->tmp_line)
	{
		free(data->tmp_line);
		data->tmp_line = NULL;
	}
	if (data)
		free(data);
	close_fds();
	write(2, msg, ft_strlen(msg)); 
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
