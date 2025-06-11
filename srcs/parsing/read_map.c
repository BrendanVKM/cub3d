/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:16:54 by bvictoir          #+#    #+#             */
/*   Updated: 2025/06/11 13:38:44 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**read_map_content(int fd2, char **map, int map_size)
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
