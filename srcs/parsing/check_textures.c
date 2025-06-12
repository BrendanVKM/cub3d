/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:40:28 by bvkm              #+#    #+#             */
/*   Updated: 2025/06/12 14:09:09 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	verif_color(char **split, int **rgb)
{
	int		i;
	int		r;
	char	*tmp;

	if (!split || !*rgb)
		return (0);
	i = 0;
	r = 1;
	tmp = NULL;
	while (split[i])
	{
		if (!split[i][0])
			r = 0;
		tmp = ft_strtrim(split[i], " \f\n\r\t\v");
		if (!ft_isnum(tmp))
			r = 0;
		free(tmp);
		i++;
	}
	if (i != 3)
		r = 0;
	return (r);
}

static uint32_t	add_rgb(t_data *data, int **rgb, char *line)
{
	uint32_t	i;
	char		**split;

	i = 0;
	split = ft_split(line, ',');
	*rgb = malloc(sizeof(int) * 3);
	free(line);
	if (!verif_color(split, rgb))
		rgb_error(data, rgb, split);
	while (split[i])
	{
		(*rgb)[i] = ft_atoi(split[i]);
		if ((*rgb)[i] < 0 || (*rgb)[i] > 255)
			rgb_error(data, rgb, split);
		i++;
	}
	ft_free_tab(&split);
	i = (*rgb)[0] << 16 | (*rgb)[1] << 8 | (*rgb)[2];
	free(*rgb);
	return (i);
}

static int	check_color(t_data *data, char f_c, char *line)
{
	if (f_c == 'F' && data->text->floor_rgb)
	{
		free(line);
		exit_data_p(data, "Error: Floor color already set");
	}
	else if (f_c == 'C' && data->text->ceiling_rgb)
	{
		free(line);
		exit_data_p(data, "Error: Ceiling color already set");
	}
	return (1);
}

static void	get_color(t_data *data, char *line)
{
	char	*tmp;
	char	f_c;

	f_c = line[0];
	tmp = ft_strtrim(line + 2, " \f\n\r\t\v");
	if (!tmp)
		exit_data_p(data, "Error: get_color memory allocation failed");
	check_color(data, f_c, tmp);
	if (f_c == 'F')
		data->text->floor = add_rgb(data, &data->text->floor_rgb, tmp);
	else if (f_c == 'C')
		data->text->ceiling = add_rgb(data, &data->text->ceiling_rgb, tmp);
}

int	parse_texture(t_data *data, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) && !data->text->path[NO])
		return (data->text->path[NO] = ft_strdup(line + 3), 1);
	else if (!ft_strncmp(line, "SO ", 3) && !data->text->path[SO])
		return (data->text->path[SO] = ft_strdup(line + 3), 1);
	else if (!ft_strncmp(line, "WE ", 3) && !data->text->path[WE])
		return (data->text->path[WE] = ft_strdup(line + 3), 1);
	else if (!ft_strncmp(line, "EA ", 3) && !data->text->path[EA])
		return (data->text->path[EA] = ft_strdup(line + 3), 1);
	else if (!ft_strncmp(line, "F ", 2))
		return (get_color(data, line), 1);
	else if (!ft_strncmp(line, "C ", 2))
		return (get_color(data, line), 1);
	return (0);
}
