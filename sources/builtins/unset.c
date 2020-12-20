/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:34:02 by psemsari          #+#    #+#             */
/*   Updated: 2020/12/15 16:44:21 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unset(t_list *arg, t_list *env)
{
	t_var_env	*var_env;
	t_list		*before;
	t_list		*base;

	base = env;
	arg = arg->next;
	while (arg != NULL)
	{
		env = base;
		var_env = (t_var_env *)env->content;
		while (ft_strncmp(var_env->key, arg->content, ft_strlen(var_env->key)))
		{
			before = env;
			env = env->next;
			if (env == NULL)
				return (1);
			var_env = (t_var_env *)env->content;
		}
		before->next = env->next; //free
		arg = arg->next;
	}
	return (0);
}
