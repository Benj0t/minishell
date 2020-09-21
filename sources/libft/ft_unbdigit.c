/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unbdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:24:44 by psemsari          #+#    #+#             */
/*   Updated: 2019/11/25 16:29:16 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_unbdigit(unsigned int n)
{
	int		resu;

	if (n == 0)
		return (1);
	resu = 0;
	while (n != 0)
	{
		n = n / 10;
		resu++;
	}
	return (resu);
}
