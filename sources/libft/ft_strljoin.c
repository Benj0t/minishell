/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strljoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 15:41:42 by psemsari          #+#    #+#             */
/*   Updated: 2020/01/05 15:56:10 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strljoin(char const *s1, char const *s2, size_t n1, size_t n2)
{
	char	*ptr;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (n1 + n2 + 1));
	if (!ptr)
		return (NULL);
	ptr[n1 + n2] = '\0';
	ret = ptr;
	while (n1 > 0)
	{
		*ptr++ = *s1++;
		n1--;
	}
	while (n2 > 0)
	{
		*ptr++ = *s2++;
		n2--;
	}
	return (ret);
}
