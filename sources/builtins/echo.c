/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:12:28 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/20 12:23:39 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **arg)
{
	int		opt_n;

	opt_n = 0;
	arg++;
	if (*arg && !ft_strncmp(*arg, "-n", 3))
	{
		opt_n = 1;
		arg++;
	}
	while (*arg)
	{
		ft_putstr_fd(*arg, 1);
		arg++;
		if (*arg)
			ft_putchar_fd(' ', 1);
	}
	if (!opt_n)
		ft_putchar_fd('\n', 1);
	return (0);
}
