/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:10:46 by bvictoir          #+#    #+#             */
/*   Updated: 2025/05/28 15:02:17 by lemarian         ###   ########.fr       */
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

static int	ft_check_args(int ac, char **av, t_data *data)
{
	int	fd;

	if (ac != 2)
		free_data_p(data, "Error: Wrong number of arguments");
	if (ft_check_file_extension(av[1], ".cub") == 0)
		free_data_p(data, "Error: Wrong file extension\n");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		free_data_p(data, "Error: File does not exist\n");
	if (read(fd, NULL, 0) == -1)
		free_data_p(data, "Error: File is not readable\n");
	return (fd);
}

int	main(int ac, char **av)
{
	int fd;
	t_data *data;
	t_raycast	*rc;
	
	data = malloc(sizeof(t_data));
	rc = malloc(sizeof(t_raycast));
	init(data);
	fd = ft_check_args(ac, av, data);
	data->rc = rc;
	parse_file(data, fd, av[1]);
	close(fd);
	printf("Parsing complete\n");
	init_player_dir(data, rc);
	if (!set_up_mlx(data, data->text))
		exit(ft_printf(2, "Error: Failed to initialize mlx\n"));
	//raycast(data);
	mlx_loop_hook(data->mlx, raycast, data);
	mlx_hook(data->win, DestroyNotify, 0, &exit_game, data);
	mlx_hook(data->win, 02, (1L << 0), &movement, data);
	mlx_hook(data->win, KeyRelease, StructureNotifyMask, &movement, data);
	mlx_loop(data->mlx);
	return (0);
}
