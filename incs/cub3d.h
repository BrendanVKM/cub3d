/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:14:34 by bvictoir          #+#    #+#             */
/*   Updated: 2025/04/14 16:06:28 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>
#include <stdint.h>

#define TILE_SIZE 30 
#define FOV 66
#define SPEED 4 // ?
#define TEX_WIDTH 64 // replace with var in struct later
# define TEX_HEIGHT 64 // idem

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

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_raycast
{
	t_vec	p_pos;
	t_vec	p_dir;
	t_vec	plane;
	t_vec	ray_dir;
	t_vec	ray_pos;
	t_vec	delta_d;
	t_vec	side_d;
	int		side; // not sure I'll keep this here
	int		step_x;
	int		step_y;
	int		wall_height;
	int		wall_start;
	int		wall_end;
}	t_raycast;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		p_pos_x;
	int		p_pos_y;
	t_config	*config;// maybe put map in data not config
}	t_data;


void	parse_file(t_config *config, int fd);
void	init_vector(t_vec *vector, double x, double y);
void	init_player_dir(t_data *data, t_raycast *rc, int x, int y);
void	ray_cast(t_data *data);
void	texture_rendering(t_data *data, t_raycast *rc, double ray_dist );

#endif


