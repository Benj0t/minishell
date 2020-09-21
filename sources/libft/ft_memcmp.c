/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:45:38 by psemsari          #+#    #+#             */
/*   Updated: 2019/10/12 15:56:08 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*chars1;
	unsigned char	*chars2;

	i = 0;
	chars1 = (unsigned char *)s1;
	chars2 = (unsigned char *)s2;
	while (i < n)
	{
		if (chars1[i] != chars2[i])
			return (chars1[i] - chars2[i]);
		i++;
	}
	return (0);
}
