/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:34:02 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/07 15:09:55 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define EENOUGH "unset: not enough arguments"

int		unset(char **arg, t_list *env)
{
	t_var_env	*var_env;
	t_list		*before;
	t_list		*base;

	if (!arg[1])
	{
		ft_putstr_fd(EENOUGH, 2);
		return (1);
	}
	base = env;
	while (*arg != NULL)
	{
		env = base;
		var_env = (t_var_env *)env->content;
		while (ft_strncmp(var_env->key, *arg, ft_strlen(var_env->key)))
		{
			before = env;
			env = env->next;
			if (env == NULL)
				return (1);
			var_env = (t_var_env *)env->content;
		}
		before->next = env->next; //free
		arg++;
	}
	return (0);
}
