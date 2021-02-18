/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:34:02 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/18 15:03:54 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define EENOUGH "unset: not enough arguments"

int		unset(char **arg)
{
	t_var_env	*var_env;
	t_list		*before;
	t_list		*base;

	if (!arg[1])
	{
		ft_putstr_fd(EENOUGH, 2);
		return (1);
	}
	base = g_env;
	while (*arg != NULL)
	{
		g_env = base;
		var_env = (t_var_env *)g_env->content;
		while (ft_strncmp(var_env->key, *arg, ft_strlen(var_env->key)))
		{
			before = g_env;
			g_env = g_env->next;
			if (g_env == NULL)
				return (1);
			var_env = (t_var_env *)g_env->content;
		}
		before->next = g_env->next; //free
		arg++;
	}
	return (0);
}
