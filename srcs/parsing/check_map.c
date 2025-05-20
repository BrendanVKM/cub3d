/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:55:41 by bvictoir          #+#    #+#             */
/*   Updated: 2025/05/20 13:30:48 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

char	set_player(t_data *data, char **map, int i, int j)
{
	if (data->p_pos.x != -1 || data->p_pos.y != -1)
		return ('2');
	data->p_pos.x = i;
	data->p_pos.y = j;
	data->orientation = map[i][j];
	return	('0');
	
} 

int	is_wall_floor(char **map, int i, int j)
{
	if (map[i-1][j] != '1' && map[i-1][j] != '0' && !is_player(map[i-1][j]))
		return (2);
	if (map[i+1][j] != '1' && map[i+1][j] != '0' && !is_player(map[i+1][j]))
		return (2);
	if (map[i][j-1] != '1' && map[i][j-1] != '0' && !is_player(map[i][j-1]))
		return (2);
	if (map[i][j+1] != '1' && map[i][j+1] != '0' && !is_player(map[i+1][j+1]))
		return (2);
	return (0);
}


int check_interior(char **map, int end, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
				map[i][j] = set_player(data, map, i, j);
			if (!(map[i][j] == '1' || map[i][j] == '0' || map[i][j] == ' ')) 
				return (2);
			if (map[i][j] == '0')
				if (is_wall_floor(map, i, j))
					return (2);
			j++;
		}
		if (map[i][j - 1] != '1')
			return (2);
		i++;
	}
	return (0);
}


int	check_extreme(char **map, int end)
{
	int	i;

	i = 0;
	while (map[0][i] || map[end - 1][i])
	{
		if (map[0][i] != '1' || map[0][i] != ' ')
			return (1);
		if (map[end - 1][i] != '1' || map[end - 1][i] != ' ')
			return (1);
		i++;
	}
	if (map[0][i] != '1' || map[end - 1][i] != '1')
		return (2);
	i = 0;
	while (map[i][0])
		if (map[i][0] != '1' || map[i][0] != ' ')
			return (1);
	return (0);
}

void	check_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
		i++;
	data->map_width = i;
	check_extreme(data->map, i);
	check_interior(data->map, i, data);
}