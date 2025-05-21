/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data->map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:55:41 by bvictoir          #+#    #+#             */
/*   Updated: 2025/05/21 11:22:37 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

char	set_player(t_data *data, int i, int j)
{
	if (data->p_pos.x != -1 || data->p_pos.y != -1)
		return ('2');
	data->p_pos.x = i;
	data->p_pos.y = j;
	data->orientation = data->map[i][j];
	data->map[i][j] = '0';
	return	('0');
	
} 

int	is_wall_floor(t_data *data, int i, int j)
{
	if (data->map[i-1][j] != '1' && data->map[i-1][j] != '0' && !is_player(data->map[i-1][j]))
		return (2);
	if (data->map[i+1][j] != '1' && data->map[i+1][j] != '0' && !is_player(data->map[i+1][j]))
		return (2);
	if (data->map[i][j-1] != '1' && data->map[i][j-1] != '0' && !is_player(data->map[i][j-1]))
		return (2);
	if (data->map[i][j+1] != '1' && data->map[i][j+1] != '0' && !is_player(data->map[i][j+1]))
		return (2);
	return (0);
}


int check_interior(t_data *data, int end)
{
	int	i;
	int	j;
	(void) end;

	i = 0;
	while (data->map[i])
	{
		j = 1;
		while (data->map[i][j])
		{
			if (is_player(data->map[i][j]))
				data->map[i][j] = set_player(data, i, j);
			if (!(data->map[i][j] == '1' || data->map[i][j] == '0' || data->map[i][j] == ' ')) 
				return (2);
			if (data->map[i][j] == '0')
				if (is_wall_floor(data, i, j))
					return (2);
			j++;
		}
		if (data->map[i][j - 1] != '1')
			return (2);
		i++;
	}
	return (0);
}


int	check_extreme(t_data *data, int nb)
{
	int	i;

	i = 0;
	while (data->map[nb][i])
	{
		if (data->map[nb][i] != '1' && data->map[nb][i] != ' ')
			return (1);
		i++;
	}
	i = 0;
	while (data->map[i] && data->map[i][0])
	{
		if (data->map[i][0] != '1' && data->map[i][0] != ' ')
			return (4);
		i++;
	}
	return (0);
}

void	check_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
		i++;
	data->map_width = i;
	for (int j = 0; data->map[j]; j++)
		printf("%s\n", data->map[j]);
	printf("%d\n", check_extreme(data, 0)); 
	printf("%d\n", check_extreme(data, i-1)); // exit dans la fonction ou apres ?
	printf("%d\n", check_interior(data, i)); // same
	printf("Player position: (%f, %f)\n", data->p_pos.x, data->p_pos.y);
	printf("Orientation: %c\n", data->orientation);
}