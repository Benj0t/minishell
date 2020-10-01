/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:40:51 by psemsari          #+#    #+#             */
/*   Updated: 2020/10/01 20:43:00 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var_env	*malloc_varenv(char *key, char *str)
{
	t_var_env	*ret;
	ret = (t_var_env *)malloc(sizeof(t_var_env));
	ret->key = key;
	ret->var = str;
	return (ret);
}

char	*get_env_var(char *search, t_list *lst_env)
{
	t_var_env *var_env;

	var_env = (t_var_env *)lst_env->content;
	while (ft_strncmp(var_env->key, search, ft_strlen(var_env->key)))
	{
		lst_env = lst_env->next;
		if (lst_env == NULL)
			return (NULL);
		var_env = (t_var_env *)lst_env->content;
	}
	return (var_env->var);
}

t_list	*envp_to_list(char **envp)
{
	int		i;
	char	*c;
	t_list	*ret;
	char	**split;

	ret = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		c = ft_strchr(envp[i], '=');
		c[0] = '\0';
		if (i == 0)
			ret = ft_lstnew(malloc_varenv(envp[i], &c[1]));
		else
			ft_lstadd_back(&ret, ft_lstnew(malloc_varenv(envp[i], &c[1])));
		i++;
	}
	return (ret);
}
