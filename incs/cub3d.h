/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:14:34 by bvictoir          #+#    #+#             */
/*   Updated: 2025/03/25 11:40:50 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"


# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define ESC 65307
# define LEFT 65361
# define RIGHT 65363

# define W 119
# define A 97
# define S 115
# define D 100
#endif

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;