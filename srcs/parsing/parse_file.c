/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:11:59 by bvictoir          #+#    #+#             */
/*   Updated: 2025/05/29 13:00:45 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**parse_map(int fd, char *line, int i, char *file)
{
	char	**map;
	char	*tmp;
	int		j;
	int		fd2;
	
	j = i;
	while ((line = get_next_line(fd)))
	{
		free(line);
		j++;
	}
	fd2 = open(file, O_RDONLY);
	map = malloc(sizeof(char *) * (j - i + 2));
	if (fd2 == -1 || !map)
	{
		if (map)
			free(map);
		return (NULL);
	}
	while (i--)
	{
		free(line);
		line = get_next_line(fd2);
	}
	i = 0;
	free(line);
	while ((line = get_next_line(fd2)))
	{
		if (line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			return (NULL);
		}
		tmp = ft_strtrim(line, "\n");
		map[i++] = ft_strdup(tmp);
		free(tmp);
		free(line);
		if (!map[i - 1])
		{
			ft_free_tab(&map);
			return (NULL);
		}
	}
	map[i] = NULL;
	return (map);
}

t_data	*parse_file(t_data *data, int fd, char *file)
{
	char	*line;
	char	*tmp;
	int		i;
	int		nb_elem;

	i = 0;
	nb_elem = 0;
	while ((tmp = get_next_line(fd)))
	{
		if (data->tmp_line)
			free(data->tmp_line);
		line = ft_strtrim(tmp, " \f\n\r\t\v");
		free(tmp);
		data->tmp_line = line;
		if (parse_texture(data, line))
			nb_elem++;
		else if (line[0] == '1')
			break ;
		else if (line[0] != '\0' && line[0] != '\n')
			exit_data_p(data, "Error: Incorrect File\n");
		i++;
	}
	if (nb_elem != 6)
		exit_data_p(data, "Error: Missing Texture\n");
	data->map = parse_map(fd, line, i, file);
	free(line);
	data->tmp_line = NULL;
	if (!data->map)
		exit_data_p(data, "Error: Incorrect Map file\n"); 
	check_map(data);
	close(fd);
	return (data);
}
