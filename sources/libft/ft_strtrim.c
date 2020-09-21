/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:49:56 by psemsari          #+#    #+#             */
/*   Updated: 2019/10/26 13:12:14 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_test_char(char const c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	while (ft_test_char(*s1, set))
		s1++;
	if (*s1 == 0)
	{
		if (!(ptr = ft_calloc(sizeof(char), 1)))
			return (NULL);
		else
			return (ptr);
	}
	len = ft_strlen(s1);
	while (ft_test_char(s1[len - 1], set))
		len--;
	if (!(ptr = ft_substr(s1, 0, len)))
		return (NULL);
	return (ptr);
}
