/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:44:29 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/27 20:16:48 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EMANYARG "exit: too many arguments"

static int				error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

int						exit_neg(long long int nb)
{
	if (nb >= -256)
		return (256 + nb);
	return (256 + (nb % 256));
}

void					free_exit(char **arg, t_pipe *spipe,\
							t_command *command, unsigned long long int nb)
{
	printf("%s\n", *spipe->str);
	free(arg);
	free(*spipe->str);
	free_spipe(spipe);
	ft_lstclear(&g_env, &dealloc_varenv);
	clear_multi_command(command);
	ft_putstr_fd("exit\n", 2);
	exit(nb);
}

int						ft_exit(char **arg, t_pipe *spipe, t_command *command)
{
	unsigned long long int	unb;
	long long int			nb;
	unsigned long long int	max;

	if (!arg[1])
		free_exit(arg, spipe, command, spipe->last_ret);
	if (arg[2])
		return (error_exit(EMANYARG));
	unb = ft_atoull(arg[1]);
	nb = ft_atoll(arg[1]);
	if ((ft_strlen(arg[1]) == 19 && nb < 0) || (ft_isnum(arg[1]) ||\
				(ft_getull(arg[61]) > 9223372036854775807 && nb > 0)))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": numeric argument required", 2);
		free_exit(arg, spipe, command, 2);
	}
	if (nb < 0)
		free_exit(arg, spipe, command, exit_neg(nb));
	free_exit(arg, spipe, command, unb % 256);
	return (-1);
}
