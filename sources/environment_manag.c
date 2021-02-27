/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_manag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:17:32 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/27 13:26:20 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		dealloc_tab(char **tab)
{
	char	**start;

	start = tab;
	while (*tab != NULL)
	{
		free(*tab);
		tab++;
	}
	free(start);
}

char		*get_env(const char *name)
{
	t_list		*tmp_env;

	if (name == NULL)
		return (NULL);
	tmp_env = g_env;
	while (tmp_env != NULL)
	{
		if (!ft_strcmp(((t_var_env *)tmp_env->content)->key, name))
			return (((t_var_env *)tmp_env->content)->var);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

t_var_env	*getvar_env(const char *name)
{
	t_list		*tmp_env;

	tmp_env = g_env;
	while (tmp_env != NULL)
	{
		if (!ft_strcmp(((t_var_env *)tmp_env->content)->key, name))
			return ((t_var_env *)tmp_env->content);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}
