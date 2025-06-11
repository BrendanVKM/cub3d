/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:11:59 by bvictoir          #+#    #+#             */
/*   Updated: 2025/06/11 14:47:54 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_and_trim_line(t_data *data, int fd)
{
	char	*tmp;
	char	*line;

	tmp = get_next_line(fd);
	if (!tmp)
		return (NULL);
	if (data->tmp_line)
	{
		free(data->tmp_line);
		data->tmp_line = NULL;
	}
	line = ft_strtrim(tmp, " \f\n\r\t\v");
	free(tmp);
	if (!line)
	{
		if (data->tmp_line)
		{
			free(data->tmp_line);
			data->tmp_line = NULL;
		}
		exit_data_p(data, "Error: Memory allocation failed");
	}
	data->tmp_line = line;
	return (line);
}

static int	process_texture_line(t_data *data, char *line, int *nb_elem)
{
	if (parse_texture(data, line))
	{
		(*nb_elem)++;
		return (1);
	}
	else if (line[0] == '1')
		return (0);
	else if (line[0] != '\0' && line[0] != '\n')
		exit_data_p(data, "Error: Incorrect File");
	return (1);
}

static int	parse_texture_section(t_data *data, int fd)
{
	char	*line;
	int		i;
	int		nb_elem;

	i = 0;
	nb_elem = 0;
	line = read_and_trim_line(data, fd);
	while (line)
	{
		if (!process_texture_line(data, line, &nb_elem))
			break ;
		line = read_and_trim_line(data, fd);
		i++;
	}
	if (nb_elem != 6)
		exit_data_p(data, "Error: Missing Texture");
	return (i);
}

static void	finalize_parsing(t_data *data, int fd, char *line)
{
	int		i;
	char	*txt;

	if (line)
		free(line);
	data->tmp_line = NULL;
	i = 0;
	txt = NULL;
	while (i < 4)
	{
		txt = ft_strtrim(data->text->path[i], " \f\n\r\t\v");
		if (!txt)
			exit_data_p(data, "Error: Memory allocation failed");
		free(data->text->path[i]);
		data->text->path[i++] = txt;
	}
	if (!data->map)
		exit_data_p(data, "Error: Incorrect Map file");
	check_map(data);
	close(fd);
}

t_data	*parse_file(t_data *data, int fd, char *file)
{
	int	texture_lines;

	texture_lines = parse_texture_section(data, fd);
	data->map = parse_map(fd, texture_lines, file);
	finalize_parsing(data, fd, data->tmp_line);
	return (data);
}
