/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_manag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:17:32 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/22 21:42:18 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*envp_to_list(char **envp)
{
	int		i;
	char	*c;
	t_list	*ret;

	ret = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		c = ft_strchr(envp[i], '=');
		c[0] = '\0';
		if (i == 0)
		{
			ret = ft_lstnew(malloc_varenv(envp[i], &c[1]));
			if (ret == NULL)
				return (NULL);
		}
		else
		{
			ft_lstadd_back(&ret, ft_lstnew(malloc_varenv(envp[i], &c[1])));
			if (ret == NULL)
				return (NULL);
		}
		i++;
	}
	return (ret);
}

char		**list_to_envp(void)
{
	int		len;
	int		i;
	char	**ret;
	t_list	*tmp;

	tmp = g_env;
	len = ft_lstsize(tmp);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (tmp != NULL)
	{
		ret[i] = ft_strjoin_c(((t_var_env *)tmp->content)->key,
					((t_var_env *)tmp->content)->var, '=');
		if (ret[i] == NULL)
		{
			dealloc_tab(ret);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	ret[len] = NULL;
	return (ret);
}

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
		if (!strcmp(((t_var_env *)tmp_env->content)->key, name))
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
		if (!strcmp(((t_var_env *)tmp_env->content)->key, name))
			return ((t_var_env *)tmp_env->content);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}
