/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:11:59 by bvictoir          #+#    #+#             */
/*   Updated: 2025/05/19 12:31:53 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			return (NULL);
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
		exit(ft_printf(2, "Error: Duplicat/Missing Texture\n")); // a proteger
	}
	data->map = parse_map(fd, line, i, file);
	if (!data->map)
	{
		free(line);
		exit(ft_printf(2, "Error: Incorrect Map \n")); // a proteger
	}
	free(line);
	close(fd);
	return (data);
}
