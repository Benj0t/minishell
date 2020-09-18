/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbdigitll16.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:05:47 by psemsari          #+#    #+#             */
/*   Updated: 2020/03/19 17:34:35 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_nbdigitll16(unsigned long long int n)
{
	int		resu;

	if (n == 0)
		return (1);
	resu = 0;
	while (n != 0)
	{
		n = n / 16;
		resu++;
	}
	return (resu);
}
