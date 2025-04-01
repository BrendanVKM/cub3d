/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:24:01 by lemarian          #+#    #+#             */
/*   Updated: 2025/04/01 17:34:22 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//t_vec = vector var type?
//additional struct just for ray?

typedef struct s_player
{
	int	pos_x;
	int	pos_y;
	double	angle;
	float	fov; // might define somewhere else
}	t_player;

typedef struct s_data
{
	char	**map;
	t_player	*player;
	int	start_x; // needed? just set player pos_x then later change
	int	start_y;
	int	map_w;
	int	map_h;
}	t_data;

