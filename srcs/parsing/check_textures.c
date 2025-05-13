/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:40:28 by bvkm              #+#    #+#             */
/*   Updated: 2025/05/08 15:43:54 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t add_rgb(t_data *data, int **rgb, char *line)
{
	int		i;
	char	**split;
	(void)	data; // pour free ensuite
	
	split = ft_split(line, ',');
	*rgb = malloc(sizeof(int) * 3);
	if (!split || !*rgb)
		exit(ft_printf(2, "Error: Malloc fail\n")); // a proteger
	i = 0;
	while (split[i])
	{
		if (i > 2)
		exit(ft_printf(2, "Error: Too many RGB values\n")); // a proteger
		(*rgb)[i] = ft_atoi(split[i]);
		if ((*rgb)[i] < 0 || (*rgb)[i] > 255)
			exit(ft_printf(2, "Error: RGB value out of range\n")); // a proteger
		i++;
	}
	ft_free_tab(&split);
	return (((*rgb)[0] << 16) | ((*rgb)[1] << 8) | (*rgb)[2]);
}

static int check_color(t_data *data, char *line)
{
	if (!ft_strncmp(line, "F ", 2) && data->text->floor_rgb)
		exit(ft_printf(2, "Error: Floor color already set\n")); // a proteger
	else if (!ft_strncmp(line, "C ", 2) && data->text->ceiling_rgb)
		exit(ft_printf(2, "Error: Ceiling color already set\n")); // a proteger
	return (1);
}

static void get_color(t_data *data, char *line)
{
	check_color(data, line);
	if (!ft_strncmp(line, "F ", 2))
	data->text->floor = add_rgb(data, &data->text->floor_rgb, line + 2);
	else if (!ft_strncmp(line, "C ", 2))
	data->text->ceiling = add_rgb(data, &data->text->ceiling_rgb, line + 2);
}

int	parse_texture(t_data *data, char *line)
{
	if(!ft_strncmp(line, "NO ", 3) && !data->text->path[NO])
		return (data->text->path[NO] = ft_strdup(line + 3), 1);
	else if(!ft_strncmp(line, "SO ", 3) && !data->text->path[SO])
		return (data->text->path[SO] = ft_strdup(line + 3), 1);
	else if(!ft_strncmp(line, "WE ", 3) && !data->text->path[WE])
		return (data->text->path[WE] = ft_strdup(line + 3), 1);
	else if(!ft_strncmp(line, "EA ", 3) && !data->text->path[EA])
		return (data->text->path[EA] = ft_strdup(line + 3), 1);
	else if(!ft_strncmp(line, "F ", 2))
		return (get_color(data, line), 1);
	else if(!ft_strncmp(line, "C ", 2))
		return (get_color(data, line), 1);
	return (0);
}