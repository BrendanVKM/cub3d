/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:52 by bvictoir          #+#    #+#             */
/*   Updated: 2025/04/24 14:25:55 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map(t_config *config, int fd)
{
	int		nb_lines;
	char	*line;
	(void)config;

	printf("get_map\n");
	nb_lines = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		
		nb_lines++;
		free(line);
	}
}