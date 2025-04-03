/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:11:59 by bvictoir          #+#    #+#             */
/*   Updated: 2025/04/03 10:57:47 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	all_textures_set(t_config *config)
{
	
	if (config->no && config->so && config->we && config->ea)
		return (1);
	return (0);
}

static char	*get_wall(char *line)
{
	char	*path;
	
	if (ft_strlen(line) < 3)
		exit(ft_printf(2, "Error: Invalid texture\n")); // a proteger
	if (line[2] != ' ')
		exit(ft_printf(2, "Error: Missing space for texture\n")); // a proteger
	path = ft_strtrim(line + 3, " ");
	if (!path || path[0] == '\0')
		exit(ft_printf(2, "Error: No Path\n")); // a proteger
	return (path);
	
}

static t_color	get_floor_ceiling(char *line)
{
	t_color	color;
	char	*line_t;
	char	**rgb;
	
	line_t = ft_strtrim(line, "");
	rgb = ft_split(line_t, ',');
	free(line_t);
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

static int	get_textures(t_config *config, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		config->no = get_wall(line);
	else if (!ft_strncmp(line, "SO", 2))
		config->so = get_wall(line);
	else if (!ft_strncmp(line, "WE", 2))
		config->we = get_wall(line);
	else if (!ft_strncmp(line, "EA", 2))
		config->ea = get_wall(line);
	else if (!ft_strncmp(line, "F", 1))
		config->floor = get_floor_ceiling(line + 2);
	else if (!ft_strncmp(line, "C", 1))
		config->ceiling = get_floor_ceiling(line + 2);
	else if (line)
		return (1);
	return (0);
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
		if (all_textures_set(config))
		{
			free(line);
			return ;
		}
		if (get_textures(config, line))
		{
			free(line);
			exit(ft_printf(2, "Error: Invalid line in file\n")); // a proteger
		}
		free(line);
	}
	free(line);
}
