/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:14:48 by psemsari          #+#    #+#             */
/*   Updated: 2020/02/17 15:38:52 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrem(char *str, int c)
{
	int		i;
	size_t	count;
	char	*result;

	i = ft_strlen(str);
	count = 0;
	while (*str)
	{
		(*str == c) ? count++ : 0;
		str++;
	}
	i -= count;
	result = (char *)ft_calloc(i + 1, 1);
	if (result == NULL)
		return (NULL);
	while (i >= 0)
	{
		if (*str != c)
		{
			result[i] = *str;
			i--;
		}
		str--;
	}
	return (result);
}
