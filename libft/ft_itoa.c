/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:12:29 by psemsari          #+#    #+#             */
/*   Updated: 2019/11/28 18:02:11 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long long int n)
{
	int		nbdigit;
	int		neg;
	char	*ptr;

	neg = 0;
	nbdigit = ft_nbdigit(n);
	if (n < 0)
		neg = 1;
	if (!(ptr = (char*)malloc(sizeof(char) * ((nbdigit + 1)))))
		return (NULL);
	ptr[nbdigit] = '\0';
	if (neg)
		ptr[0] = '-';
	if (n == 0)
		ptr[0] = '0';
	while (n != 0)
	{
		nbdigit--;
		ptr[nbdigit] = (neg) ? (n % 10) * -1 + '0' : (n % 10) + '0';
		n /= 10;
	}
	return (ptr);
}
