/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:27:28 by bvictoir          #+#    #+#             */
/*   Updated: 2025/06/12 11:17:56 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>
# include <stdint.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define FOV 60
# define SPEED 0.03
# define ROT 0.02

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define ESC 65307
# define LEFT 65361
# define RIGHT 65363

# define W 119
# define A 97
# define S 115
# define D 100
# define RIGHT 65363
# define LEFT 65361

typedef enum e_direction
{
	NO,
	SO,
	EA,
	WE
}				t_direction;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			size_line;
	int			bpp;
	int			endian;
}				t_image;

typedef struct s_texture
{
	void		*img[4];
	char		*path[4];
	int			*width[4];
	int			*height[4];
	char		*addr[4];
	int			*floor_rgb;
	int			*ceiling_rgb;
	uint32_t	floor;
	uint32_t	ceiling;
	int			dir;
}				t_texture;

typedef struct s_vec
{
	double		x;
	double		y;
}				t_vec;

typedef struct s_raycast
{
	t_vec		p_dir;
	t_vec		plane;
	t_vec		ray_dir;
	int			map_x;
	int			map_y;
	t_vec		delta_d;
	t_vec		side_d;
	int			side;
	int			step_x;
	int			step_y;
	double		ray_dist;
	int			wall_height;
	int			wall_start;
	int			wall_end;
}				t_raycast;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_image		*image;
	char		*tmp_line;
	char		**map;
	t_vec		p_pos;
	t_direction	orientation;
	t_raycast	*rc;
	t_texture	*text;
}				t_data;

void			init(t_data *data);
void			check_map(t_data *data);
void			rot_left(t_raycast *rc);
void			rot_right(t_raycast *rc);
void			exit_error(t_data *data, char *mess);
void			exit_data_p(t_data *data, char *msg);
void			init_player_dir(t_data *data, t_raycast *rc);
void			rgb_error(t_data *data, int **rgb, char **split);
void			init_raycast(t_data *data, t_raycast *ray, double cam_x);
void			draw_wall(t_data *data, t_raycast *rc, t_texture *text, int x);
void			draw_ceiling_floor(t_raycast *rc, t_texture *text,
					t_image *image, int x);

int				get_tex_y(double tex_pos, t_texture *text);
int				set_up_mlx(t_data *data, t_texture *text);
int				parse_texture(t_data *data, char *line);
int				movement(int key_code, t_data *data);
int				get_direction(t_raycast *rc);
int				exit_game(t_data *data);
int				raycast(t_data *data);

char			**parse_map(int fd, int texture_lines, char *file);
char			**read_map_content(int fd2, char **map, int map_size);

t_data			*parse_file(t_data *data, int fd, char *file);

#endif
