/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:34:02 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/06 13:05:37 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unset(char **arg, t_list *env)
{
	t_var_env	*var_env;
	t_list		*before;
	t_list		*base;
	int	i = 1;

	base = env;
	while (arg[i] != NULL)
	{
		env = base;
		var_env = (t_var_env *)env->content;
		while (ft_strncmp(var_env->key, arg[i], ft_strlen(var_env->key)))
		{
			before = env;
			env = env->next;
			if (env == NULL)
				return (1);
			var_env = (t_var_env *)env->content;
		}
		before->next = env->next; //free
		i++;
	}
	env = base;
	list_env(env);
	return (0);
}
