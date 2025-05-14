/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:55:41 by bvictoir          #+#    #+#             */
/*   Updated: 2025/05/14 12:09:42 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extreme(char **map, int end)
{
	int	j;

	j = 0;
	while (map[0][j] || map[end - 1][j])
	{
		if (map[0][j] != '1' || map[0][j] != ' ')
			return (1);
		if (map[end - 1][j] != '1' || map[end - 1][j] != ' ')
			return (1);
		j++;
	}
	if (map[0][j] != '1' || map[end - 1][j] != '1')
		return (2);
	
	return (0);
}

void	check_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
		i++;
	data->map_width = i;
	
}