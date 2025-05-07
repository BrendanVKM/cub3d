/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvkm <bvkm@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:53:25 by bvictoir          #+#    #+#             */
/*   Updated: 2025/05/07 02:43:51 by bvkm             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *data)
{
	if (!data)
		exit(ft_printf(2, "Error: Malloc fail\n"));
	data->text = malloc(sizeof(t_texture));
	if (!data->text)
		exit(ft_printf(2, "Error: Malloc fail\n"));
}
