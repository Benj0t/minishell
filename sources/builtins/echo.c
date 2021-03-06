/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:12:28 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/27 13:06:41 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_opt_n(char *arg)
{
	if (*arg != '-')
		return (0);
	arg++;
	while (*arg == 'n')
	{
		arg++;
		if (*arg == '\0')
			return (1);
	}
	return (0);
}

void		print_echo(char **arg)
{
	if (arg && *arg && arg[1] == NULL && !ft_strncmp(*arg, "~", 2))
	{
		ft_putstr_fd(get_env("HOME"), 1);
		arg++;
	}
	while (*arg)
	{
		ft_putstr_fd(*arg, 1);
		arg++;
		if (*arg)
			ft_putchar_fd(' ', 1);
	}
}

int			ft_echo(char **arg)
{
	int		opt_n;

	if (!arg || !(*arg))
	{
		ft_putchar_fd('\n', 2);
		return (0);
	}
	opt_n = 0;
	arg++;
	while (*arg && check_opt_n(*arg))
	{
		opt_n = 1;
		arg++;
	}
	print_echo(arg);
	if (!opt_n)
		ft_putchar_fd('\n', 1);
	return (0);
}
