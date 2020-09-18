/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:04:17 by psemsari          #+#    #+#             */
/*   Updated: 2019/11/19 15:16:18 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count * size == 0)
	{
		count = 1;
		size = 1;
	}
	if (!(ptr = malloc(size * count)))
		return (NULL);
	ft_bzero(ptr, count);
	return (ptr);
}
