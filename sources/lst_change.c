/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:54:15 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/27 19:10:03 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var_env	*egal_replace(char **envp, size_t i)
{
	char		*c;

	c = ft_strchr(envp[i], '=');
	c[0] = '\0';
	return (malloc_varenv(envp[i], &c[1]));
}

t_list		*envp_to_list(char **envp)
{
	int			i;
	t_list		*ret;
	t_list		*tmp;
	t_var_env	*malloc;

	ret = NULL;
	tmp = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		malloc = egal_replace(envp, i);
		if (malloc == NULL)
			return (NULL);
		tmp = ft_lstnew(malloc);
		if (tmp == NULL)
			return (NULL);
		if (i == 0)
			ret = tmp;
		else
			ft_lstadd_back(&ret, tmp);
		i++;
	}
	return (ret);
}

void		join_to_list(char **ret, int i, t_list *tmp)
{
	if (((t_var_env *)tmp->content)->var != NULL)
	{
		ret[i] = ft_strjoin_c(((t_var_env *)tmp->content)->key,\
			((t_var_env *)tmp->content)->var, '=');
	}
	else
		ret[i] = ft_strdup(((t_var_env *)tmp->content)->key);
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
		join_to_list(ret, i, tmp);
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
