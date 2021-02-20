/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:34:02 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/20 05:06:32 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export(char **arg, t_list *env)
{
	int			i;
	int j;

	i = 0;
	j = 0;
	if (arg[j] == NULL)
		print_env(env);
	while (arg[j] != NULL)
	{
		i = valid_env(arg[j]);
		if (arg[j][i] == '=') //key=value
		{
			arg[j][i] = 0;
			set_env_var(arg[j], &arg[j][i+1], env);
			return (0);
		}
		j++;
	}
	return (0);
}
