/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:40:51 by psemsari          #+#    #+#             */
/*   Updated: 2020/10/09 16:32:51 by psemsari         ###   ########.fr       */
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

char	*get_env_var(char *search, t_list *env)
{
	t_var_env *var_env;

	var_env = (t_var_env *)env->content;
	while (ft_strncmp(var_env->key, search, ft_strlen(var_env->key)))
	{
		env = env->next;
		if (env == NULL)
			return ("");
		var_env = (t_var_env *)env->content;
	}
	return (var_env->var);
}

void	set_env_var(char *key, char* var, t_list *env)
{
	ft_lstadd_back(&env, ft_lstnew(malloc_varenv(key, var)));
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

char	**list_to_envp(t_list *env)
{
	int		len;
	int		i;
	char	**ret;

	len = ft_lstsize(env);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	ret[len] = NULL;
	i = 0;
	while (env != NULL)
	{
		ret[i] = ft_strjoin_c(((t_var_env *)env->content)->key,
					((t_var_env *)env->content)->var, '=');
		env = env->next;
		i++;
	}
	return (ret);
}

void	dealloc_tab(char **tab)
{
	char	**start;

	start = tab;
	while (tab != NULL)
	{
		free(*tab);
		tab++;
	}
	free(start);
}
