/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itouhex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:48:12 by psemsari          #+#    #+#             */
/*   Updated: 2019/12/17 17:51:33 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itouhex(unsigned int n)
{
	char	*str;
	int		nbdigit;
	char	temp;

	nbdigit = ft_nbdigit16(n);
	str = (char *)ft_calloc(nbdigit + 1, sizeof(char));
	str[nbdigit] = '\0';
	while (--nbdigit >= 0)
	{
		temp = n % 16;
		if (temp > 9)
			str[nbdigit] = (temp - 10) + 'a';
		else
			str[nbdigit] = temp + '0';
		n /= 16;
	}
	return (str);
}
