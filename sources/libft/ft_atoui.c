/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:45:57 by psemsari          #+#    #+#             */
/*   Updated: 2020/08/07 15:29:43 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atoui(const char *str)
{
	int				i;
	int				test;
	unsigned int	result;

	i = 0;
	test = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (ft_isdigit((int)str[i]))
	{
		result *= 10;
		result += (int)str[i] - 48;
		if (test >= 9 && result < 1000000000)
			return ((unsigned int)4294967295);
		i++;
		test++;
	}
	return (result);
}
