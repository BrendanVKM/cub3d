/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:11:59 by bvictoir          #+#    #+#             */
/*   Updated: 2025/05/07 02:58:29 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_color(char *line)
{
	uint32_t	color;
	char		**rgb;

	rgb = ft_split(line, ',');
	if (!rgb)
		exit(ft_printf(2, "Error: Split fail\n")); // a proteger
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_free_tab(&rgb);
		exit(ft_printf(2, "Error: Invalid color\n")); // a proteger
	}
	if (!ft_isnum(rgb[0]) || !ft_isnum(rgb[1]) || !ft_isnum(rgb[2]))
	{
		ft_free_tab(&rgb);
		exit(ft_printf(2, "Error: color must be digit\n")); // a proteger
	}
	color = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | ft_atoi(rgb[2]);
	if (color > 0xFFFFFF)
	{
		ft_free_tab(&rgb);
		exit(ft_printf(2, "Error: color range [0,16777215]\n")); // a proteger
	}
	ft_free_tab(&rgb);
	return (color);
}

static int	parse_texture(t_data *data, char *line)
{
	if(!ft_strncmp(line, "NO ", 3))
		return (data->text->path[NO] = ft_strdup(line + 3), 1);
	else if(!ft_strncmp(line, "SO ", 3))
		return (data->text->path[SO] = ft_strdup(line + 3), 1);
	else if(!ft_strncmp(line, "WE ", 3))
		return (data->text->path[WE] = ft_strdup(line + 3), 1);
	else if(!ft_strncmp(line, "EA ", 3))
		return (data->text->path[EA] = ft_strdup(line + 3), 1);
	else if(!ft_strncmp(line, "F ", 2))
		return (data->text->floor = get_color(line + 2), 1);
	else if(!ft_strncmp(line, "C ", 2))
		return (data->text->ceiling = get_color(line + 2), 1);
	return (0);
}

static char	**parse_map(int fd, char *line, int i, char *file)
{
	char	**map;
	int		j;
	int		fd2;

	j = i;
	while ((line = get_next_line(fd)))
		j++;
	fd2 = open(file, O_RDONLY);
	if (fd2 == -1)
		exit(ft_printf(2, "Error: File does not exist\n")); // a proteger
	map = malloc(sizeof(char *) * (j - i + 1));	
	while (i--)
		line = get_next_line(fd2);
	while ((line = get_next_line(fd2)))
	{
		if (line[0] == '\0')
		{
			free(line);
			exit(ft_printf(2, "Error: Empty line in map\n")); // a proteger
		}
		line = ft_strtrim(line, "\n");
		map[i++] = ft_strdup(line);
	}
	return (map);
}


t_data	*parse_file(t_data *data, int fd, char *file)
{
	char	*line;
	int		i;
	int		nb_elem;
	
	i = 0;
	nb_elem = 0;
	while ((line = get_next_line(fd)))
	{
		line = ft_strtrim(line, " \f\n\r\t\v");
		if (parse_texture(data, line))
			nb_elem++;
		else if (line[0] == '1')
			break;
		i++;
		free(line);
	}
	if (nb_elem != 6)
	{
		free(line);
		exit(ft_printf(2, "Error: Missing texture or color\n")); // a proteger
	}
	data->map = parse_map(fd, line, i, file);
	free(line);
	close(fd);
	return (data);
}
