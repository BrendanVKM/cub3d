/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:14:46 by bvictoir          #+#    #+#             */
/*   Updated: 2025/06/10 11:17:00 by bvictoir         ###   ########.fr       */
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

char	**parse_map(int fd, int texture_lines, char *file)
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
