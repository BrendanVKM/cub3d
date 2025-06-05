/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:11:59 by bvictoir          #+#    #+#             */
/*   Updated: 2025/06/05 14:28:56 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!line)
			break ;
		free(line);
		line = get_next_line(fd);
		count++;
	}
	return (count);
}

static char	**allocate_map_array(int size, int fd2)
{
	char	**map;
	int		i;

	if (fd2 == -1)
		return (NULL);
	map = malloc(sizeof(char *) * (size + 1));
	if (!map)
	{
		close(fd2);
		return (NULL);
	}
	i = 0;
	while (i < size + 1)
	{
		map[i] = NULL;
		i++;
	}
	return (map);
}

static int	skip_texture_lines(int fd2, int lines_to_skip)
{
	char	*line;

	while (lines_to_skip--)
	{
		line = get_next_line(fd2);
		if (!line)
		{
			close(fd2);
			return (0);
		}
		free(line);
	}
	return (1);
}

static void	cleanup_map_error(char **map, int fd2, char *line)
{
	if (line)
		free(line);
	if (map)
		ft_free_tab(&map);
	close(fd2);
}

static int	process_map_line(char **map, char *line, int index)
{
	char	*tmp;

	if (!line || line[0] == '\0' || line[0] == '\n')
		return (0);
	tmp = ft_strtrim(line, "\n");
	if (!tmp)
		return (0);
	map[index] = ft_strdup(tmp);
	free(tmp);
	if (!map[index])
		return (0);
	return (1);
}

static char	**read_map_content(int fd2, char **map, int map_size)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd2);
	while (line && i < map_size)
	{
		if (!process_map_line(map, line, i))
		{
			cleanup_map_error(map, fd2, line);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd2);
		i++;
	}
	if (line)
		free(line);
	map[i] = NULL;
	close(fd2);
	return (map);
}

static char	**parse_map(int fd, int texture_lines, char *file)
{
	char	**map;
	int		map_lines;
	int		fd2;

	map_lines = count_map_lines(fd) + 1;
	if (map_lines == 0)
		return (NULL);
	fd2 = open(file, O_RDONLY);
	map = allocate_map_array(map_lines, fd2);
	if (!map)
		return (NULL);
	if (!skip_texture_lines(fd2, texture_lines))
	{
		ft_free_tab(&map);
		return (NULL);
	}
	return (read_map_content(fd2, map, map_lines));
}

static char	*read_and_trim_line(t_data *data, int fd)
{
	char	*tmp;
	char	*line;

	tmp = get_next_line(fd);
	if (!tmp)
		return (NULL);
	if (data->tmp_line)
		free(data->tmp_line);
	line = ft_strtrim(tmp, " \f\n\r\t\v");
	free(tmp);
	if (!line)
		exit_data_p(data, "Error: Memory allocation failed");
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
		exit_data_p(data, "Error: Incorrect File\n");
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
		exit_data_p(data, "Error: Missing Texture\n");
	return (i);
}

static void	finalize_parsing(t_data *data, int fd, char *line)
{
	if (line)
		free(line);
	data->tmp_line = NULL;
	if (!data->map)
		exit_data_p(data, "Error: Incorrect Map file\n");
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
