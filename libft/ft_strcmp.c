/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:03:17 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/06 12:55:02 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		ret;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if ((unsigned char)s1[i] - (unsigned char)s2[i] > 0)
		ret = 1;
	else if ((unsigned char)s1[i] - (unsigned char)s2[i] < 0)
		ret = -1;
	else
		ret = 0;
	return (ret);
}
