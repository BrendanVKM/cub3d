/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:00:01 by lemarian          #+#    #+#             */
/*   Updated: 2025/06/10 17:24:55 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_y(double tex_pos, t_texture *text)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= *text->height[text->dir])
		tex_y = *text->height[text->dir] - 1;
	return (tex_y);
}

int	get_direction(t_raycast *rc)
{
	if (rc->side == 0)
	{
		if (rc->ray_dir.x < 0)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (rc->ray_dir.y < 0)
			return (SO);
		else
			return (NO);
	}
}
