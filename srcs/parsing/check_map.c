/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:35:10 by bvictoir          #+#    #+#             */
/*   Updated: 2025/06/10 10:20:18 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	set_player(t_data *data, int i, int j)
{
	if (data->p_pos.x != -1 || data->p_pos.y != -1)
		return ('2');
	data->p_pos.x = j;
	data->p_pos.y = i;
	if (data->map[i][j] == 'N')
		data->orientation = NO;
	else if (data->map[i][j] == 'S')
		data->orientation = SO;
	else if (data->map[i][j] == 'E')
		data->orientation = EA;
	else if (data->map[i][j] == 'W')
		data->orientation = WE;
	data->map[i][j] = '0';
	return ('0');
}

static int	is_wall_floor(t_data *data, int i, int j)
{
	if (!data->map[i - 1] || !data->map[i + 1] || !data->map[i][j - 1]
		|| !data->map[i][j + 1])
		return (2);
	if (!strchr("NSWE10", data->map[i - 1][j]))
		return (2);
	if (!strchr("NSWE10", data->map[i + 1][j]))
		return (2);
	if (!strchr("NSWE10", data->map[i][j - 1]))
		return (2);
	if (!strchr("NSWE10", data->map[i][j + 1]))
		return (2);
	return (0);
}

static int	check_interior(t_data *data, int end)
{
	int	i;
	int	j;

	(void)end;
	i = 0;
	while (i < end - 1)
	{
		j = 1;
		while (data->map[i][j])
		{
			if (strchr("NSWE", data->map[i][j]))
				data->map[i][j] = set_player(data, i, j);
			if (!(data->map[i][j] == '1' || data->map[i][j] == '0'
					|| data->map[i][j] == ' '))
				return (2);
			if (data->map[i][j] == '0')
				if (is_wall_floor(data, i, j))
					return (2);
			j++;
		}
		if (!strchr("1 ", data->map[i][j - 1]))
			return (2);
		i++;
	}
	return (0);
}

static int	check_extreme(t_data *data, int nb)
{
	int	i;

	i = 0;
	while (data->map[nb][i])
	{
		if (!strchr("1 ", data->map[nb][i]))
			return (1);
		i++;
	}
	i = 0;
	while (data->map[i] && data->map[i][0])
	{
		if (!strchr("1 ", data->map[i][0]))
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
	if (i < 3)
		exit_data_p(data, "Error: Map too small");
	if (check_extreme(data, 0))
		exit_data_p(data, "Error: Map not closed");
	if (check_extreme(data, i - 1))
		exit_data_p(data, "Error: Map not closed");
	if (check_interior(data, i))
		exit_data_p(data, "Error: incorrect Map");
	if (data->p_pos.x == -1 || data->p_pos.y == -1)
		exit_data_p(data, "Error: Player not found in Map");
}
