/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:19:45 by psemsari          #+#    #+#             */
/*   Updated: 2019/10/24 13:07:32 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*resu;

	i = 0;
	resu = (unsigned char *)dst;
	str = (unsigned char *)src;
	while (i < n)
	{
		resu[i] = str[i];
		i++;
	}
	return ((void *)resu);
}
