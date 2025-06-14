/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvictoir <bvictoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:41:34 by bvkm              #+#    #+#             */
/*   Updated: 2024/11/04 14:22:47 by bvictoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t count)
{
	char	*str;

	str = (char *)ptr;
	while (count--)
	{
		*str = (unsigned char)value;
		str++;
	}
	return (ptr);
}
