/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:43:18 by psemsari          #+#    #+#             */
/*   Updated: 2019/10/24 13:07:37 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	const char	*lasts;
	char		*lastd;

	d = dst;
	s = src;
	lasts = s + (len - 1);
	lastd = d + (len - 1);
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
	{
		while (len--)
			*lastd-- = *lasts--;
	}
	return (dst);
}
