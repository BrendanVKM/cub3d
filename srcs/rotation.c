/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:05:53 by lemarian          #+#    #+#             */
/*   Updated: 2025/06/12 11:09:54 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rot_left(t_raycast *rc)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = rc->p_dir.x;
	rc->p_dir.x = rc->p_dir.x * cos(-ROT) - rc->p_dir.y * sin(-ROT);
	rc->p_dir.y = old_dir_x * sin(-ROT) + rc->p_dir.y * cos(-ROT);
	old_plane_x = rc->plane.x;
	rc->plane.x = rc->plane.x * cos(-ROT) - rc->plane.y * sin(-ROT);
	rc->plane.y = old_plane_x * sin(-ROT) + rc->plane.y * cos(-ROT);
}

void	rot_right(t_raycast *rc)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = rc->p_dir.x;
	rc->p_dir.x = rc->p_dir.x * cos(ROT) - rc->p_dir.y * sin(ROT);
	rc->p_dir.y = old_dir_x * sin(ROT) + rc->p_dir.y * cos(ROT);
	old_plane_x = rc->plane.x;
	rc->plane.x = rc->plane.x * cos(ROT) - rc->plane.y * sin(ROT);
	rc->plane.y = old_plane_x * sin(ROT) + rc->plane.y * cos(ROT);
}
