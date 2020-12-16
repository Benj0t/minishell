/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:34:02 by psemsari          #+#    #+#             */
/*   Updated: 2020/12/16 17:43:47 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export(t_list *arg, t_list *env)
{
	t_var_env	*var_env;
	char 		*str;
	int			i;

	i = 0;
	arg = arg->next;
	while (arg != NULL)
	{
		str = arg->content;
		while (str[i])
		{
			if (str[i] == '=') //key=value
				str[i] = 0;
			i++;
		}
		set_env_var(str, &str[i+1], env);
		arg = arg->next;
	}
	return (0);
}
