/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:44:29 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/17 23:22:27 by bemoreau         ###   ########.fr       */
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

	if (!arg[1])
		exit(0); //last value
	if (arg[2])
		return (error_exit(EMANYARG));
	exit(atoi(arg[1]));
	return (-1);
}
