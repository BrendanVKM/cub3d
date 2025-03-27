/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:11:59 by bvictoir          #+#    #+#             */
/*   Updated: 2025/03/27 13:48:17 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



static t_color	get_color(char *line)
{
	t_color	color;
	char	**rgb;
	
	rgb = ft_split(line, ',');
	if (!rgb)
		exit(ft_printf(2, "Error: Split fail\n")); // a proteger
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3] )
	{
		ft_free_tab(&rgb);
		exit(ft_printf(2, "Error: Invalid color\n"));
	}
	if (!ft_isnum(rgb[0]) || !ft_isnum(rgb[1]) || !ft_isnum(rgb[2]))
	{
		ft_free_tab(&rgb);
		exit(ft_printf(2, "Error: color must be digit\n")); // a proteger
	}
	color.r = ft_atoi(rgb[0]);
	color.g = ft_atoi(rgb[1]);
	color.b = ft_atoi(rgb[2]);
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
	{
		ft_free_tab(&rgb);
		exit(ft_printf(2, "Error: color range [0,255]\n")); // a proteger
	}
	ft_free_tab(&rgb);
	return (color);
}

void	get_textures(t_config *config, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		config->no = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		config->so = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		config->we = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		config->ea = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "F ", 2))
		config->floor = get_color(line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		config->ceiling = get_color(line + 2);
}

void	parse_file(t_config *config, int fd)
{
	char *line;

	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		get_textures(config, line);
		free(line);
	}
	free(line);
}