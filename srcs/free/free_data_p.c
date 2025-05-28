/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:57:18 by bvictoir          #+#    #+#             */
/*   Updated: 2025/05/28 14:40:07 by bvictoir         ###   ########.fr       */
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

static void	free_texture(t_data *data, t_texture *text)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (text->path[i])
			free(text->path[i]);
		i++;
	}
	if (data->text)
		free(data->text);
}

void	free_data_p(t_data *data, char *msg)
{
	free_texture(data, data->text);
	if (data->map)
		ft_free_tab(&data->map);
	if (data->tmp_line)
		free(data->tmp_line);
	if (data)
		free(data);
	ft_printf(2, "%s\n", msg);
	close_fds();
	exit(EXIT_FAILURE);
}