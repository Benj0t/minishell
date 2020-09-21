/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:31:13 by psemsari          #+#    #+#             */
/*   Updated: 2020/02/17 14:08:03 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (s2[0] == '\0')
		return ((char*)s1);
	while (s1[i] != '\0' && i < len)
	{
		while (s1[i + j] == s2[j] && i + j < len)
		{
			j++;
			if (s2[j] == '\0')
				return ((char*)s1 + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
