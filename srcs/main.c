/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:10:46 by bvictoir          #+#    #+#             */
/*   Updated: 2025/05/07 02:59:09 by bvkm             ###   ########.fr       */
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
	int	fd;

	if (ac != 2)
		exit(ft_printf(2, "Error: Wrong number of arguments\n"));
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
	int			fd;
	t_data		*data;

	fd = ft_check_args(ac, av);
	
	data = malloc(sizeof(t_data));
	init(data);
	parse_file(data, fd, av[1]);
	close(fd);
	printf("Textures:\n");
	for (int i = 0; i < 4; i++)
	{
		printf("Texture %d: %s\n", i, data->text->path[i]);
	}
	printf("\nMap:\n");
	for (int i = 0; data->map[i]; i++)
	{
		printf("%s\n", data->map[i]);
	}
	return (0);
}
