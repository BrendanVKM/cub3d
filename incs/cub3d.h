/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:14:34 by bvictoir          #+#    #+#             */
/*   Updated: 2025/03/31 12:47:42 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>

#define TILE_SIZE 30 //float? how big is a square in the map
#define FOV //field of vision of player, static
#define ROT_SPEED

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define ESC 65307
# define LEFT 65361
# define RIGHT 65363

# define W 119
# define A 97
# define S 115
# define D 100

typedef struct s_color
{
	int r;
	int g;
	int b;
}	t_color;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color floor;
	t_color ceiling;
	char	**map;
}	t_config;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_config	config;
}	t_data;


void	parse_file(t_config *config, int fd);

#endif


