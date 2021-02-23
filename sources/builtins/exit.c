/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:44:29 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/23 23:26:46 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EMANYARG "exit: too many arguments"

static int				ft_isnum(char *str)
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

static int				error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

long long int	ft_atoll(const char *str)
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
	int		neg;

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
	int		neg;

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

int						exit_neg(long long int nb)
{
	if (nb >= -256)
		return (256 + nb);
	return (256 + (nb % 256));
}


void						free_exit(char **arg, s_pipe *spipe, t_command *command)
{
	free(arg);
	free_spipe(spipe);
	ft_lstclear(&g_env, &dealloc_varenv);
}

int						ft_exit(char **arg, s_pipe *spipe, t_command *command)
{
	unsigned long long int unb;
	long long int nb;
	unsigned long long int max;

	if (!arg[1])
	{
		free_exit(arg, spipe, command);
		exit(spipe->last_ret);
	}
	if (arg[2])
		return(error_exit(EMANYARG));
	unb = ft_atoull(arg[1]);
	nb = ft_atoll(arg[1]);
	if ((ft_strlen(arg[1]) == 19 && nb < 0) || (ft_isnum(arg[1]) || (ft_getull(arg[1]) > 9223372036854775807 && nb > 0)))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": numeric argument required", 2);
		free_exit(arg, spipe, command);
		exit(2);
	}
	if (nb < 0)
	{
		free_exit(arg, spipe, command);
		exit(exit_neg(nb));
	}
	exit(unb % 256);
	return (-1);
}
