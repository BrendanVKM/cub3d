/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:10:46 by bvictoir          #+#    #+#             */
/*   Updated: 2025/04/24 16:04:32 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static int	ft_check_file_extension(char *file, char *extension)
{
	int		i;
	int		j;

	i = ft_strlen(file) - 1;
	j = ft_strlen(extension) - 1;
	while (j >= 0)
		if (file[i--] != extension[j--])
			return (0);
	return (1);
}

static int	ft_check_args(int ac, char **av)
{
	int fd;
	
	if (ac != 2)
		exit(ft_printf(2, "Error: Wrong number of arguments\n"));//need "error\n"
	if (ft_check_file_extension(av[1], ".cub") == 0)
		exit(ft_printf(2, "Error: Wrong file extension\n"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(ft_printf(2, "Error: File does not exist\n"));
	if (read(fd, NULL, 0) == -1)
	{
		close(fd);
		exit(ft_printf(2, "Error: File is not readable\n"));
	}
	return (fd);
}

int	main(int ac, char **av)
{
	int fd;
	t_texture text;
	t_data	data;
	t_raycast	rc;
	
	fd = ft_check_args(ac, av);
	parse_file(&config, fd);
	//init data
	if (!set_up_mlx(&data, &text))
		exit(ft_printf(2, "Error: Failed to initialize mlx\n"));
	init_player_dir(&data, &rc, x, y);//need player pos[y][x] at the start
	raycast(&data, &rc);
	/*
	- mlx_hook (key_press, key_release)
	- mlx_loop_hook (raycast)
	- mlx_loop
	*/
	return (0);
}
