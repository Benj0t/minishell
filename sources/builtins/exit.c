/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:44:29 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/19 14:38:36 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define EMANYARG "exit: too many arguments"

static int				ft_isnum(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
	}
	return (0);
}

static int				error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	return (-1);
}

unsigned long long int	ft_atoull(const char *str)
{
	int i;
	unsigned long long result;
	int neg;

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
	return (result * (unsigned long long int)neg);
}

int						ft_exit(char **arg, s_pipe *spipe)
{

	if (!arg[1])
		exit(spipe->last_ret);
	if (arg[2])
		return (error_exit(EMANYARG));
	if (ft_isnum(arg[1]) || ft_strlen(arg[1]) > 18)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": numeric argument required", 2);
		exit(2);
	}
	exit(ft_atoull(arg[1]) % 256);
	return (-1);
}
