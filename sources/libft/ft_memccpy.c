/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:38:16 by psemsari          #+#    #+#             */
/*   Updated: 2019/10/12 14:40:43 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
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
		if (str[i - 1] == (unsigned char)c)
			return (dst + i);
	}
	return (0);
}
