/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:16:07 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/22 21:22:57 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		join_env(const char *name, char *value)
{
	t_var_env	*tmp;
	char		*str;

	tmp = getvar_env(name);
	if (tmp)
	{
		str = tmp->var;
		if (!str)
			tmp->var = ft_strdup(value);
		else
			tmp->var = ft_strjoin(tmp->var, value);
		if (tmp->var == NULL)
			return (-1);
		if (str != NULL)
			free(str);
	}
	else if (!tmp)
		ft_lstadd_back(&g_env, ft_lstnew(malloc_varenv(name, value)));
	return (0);
}

int		put_env(char *string)
{
	size_t i;

	i = is_valid_env(string);
	if (string[i] == '\0')
		return (set_env(string, NULL, 0));
	string[i] = '\0';
	if (string[i - 1] == '+')
	{
		string[i - 1] = '\0';
		return (join_env(string, &string[i + 1]));
	}
	return (set_env(string, &string[i + 1], 1));
}

int		set_env(const char *name, char *value, int replace)
{
	t_var_env *tmp;

	tmp = getvar_env(name);
	if (replace && tmp)
	{
		free(tmp->var);
		tmp->var = ft_strdup(value);
		if (tmp->var == NULL)
			return (-1);
	}
	else if (!tmp)
		ft_lstadd_back(&g_env, ft_lstnew(malloc_varenv(name, value)));
	return (0);
}

int		contains_egal(const char *name)
{
	size_t i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		unset_env(const char *name)
{
	t_list		*tmp_env;
	t_list		*tmp;

	if (name == NULL || ft_strlen(name) == 0 || contains_egal(name))
		return (-1);
	tmp_env = g_env;
	while (tmp_env != NULL)
	{
		if (!strcmp(((t_var_env *)tmp_env->content)->key, name))
		{
			tmp->next = tmp_env->next;
			dealloc_varenv((t_var_env *)tmp_env->content);
		}
		tmp = tmp_env;
		tmp_env = tmp_env->next;
	}
	return (0);
}
