/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 13:20:04 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/27 13:23:53 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						ft_isnum(char *str)
{
	int i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
	}
	return (0);
}

long long int			ft_atoll(const char *str)
{
	int					i;
	long long			result;
	int					neg;

	i = 0;
	result = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit((int)str[i]))
	{
		result *= 10;
		result += (long long int)str[i] - 48;
		i++;
	}
	return (result * (long long int)neg);
}

unsigned long long int	ft_atoull(const char *str)
{
	int							i;
	unsigned long long int		result;
	int							neg;

	i = 0;
	result = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit((int)str[i]))
	{
		result *= 10;
		result += (unsigned long long int)str[i] - 48;
		i++;
	}
	return (result * neg);
}

unsigned long long int	ft_getull(const char *str)
{
	int							i;
	unsigned long long int		result;
	int							neg;

	i = 0;
	result = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit((int)str[i]))
	{
		result *= 10;
		result += (unsigned long long int)str[i] - 48;
		i++;
	}
	return (result);
}
