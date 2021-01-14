/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:44:29 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/07 15:03:10 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define EMANYARG "exit: too many arguments"

static int	error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	return (-1);
}

int		ft_exit(char **arg)
{
	int		n;

	if (arg[2])
		return (error_exit(EMANYARG));
	if (!arg[1])
		exit(0); //last value
	exit(atoi(arg[1]));
	return (-1);
}
