/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:35:49 by psemsari          #+#    #+#             */
/*   Updated: 2019/10/21 16:27:26 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	count = ft_strlen(dst);
	if (count >= dstsize)
		return (count + ft_strlen(src) - (count - dstsize));
	ft_strlcpy(&dst[count], src, dstsize - count);
	return (count + ft_strlen(src));
}
