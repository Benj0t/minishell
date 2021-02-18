/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:40:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/18 15:33:37 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_env(char *s)
{
	size_t i;

	i = 0;
	if (ft_isdigit(s[i]) || s[i] == '?')
		return (1);
	while (s[i])
	{
			if (!ft_isalnum(s[i]) && s[i] != '_')
			{
				if (i == 0)
					return (0);
				else
					break;
			}
		i++;
	}
	return (i);
}

int			valid_env(char *s)
{
	size_t i;

	i = 0;
	if (s[i] == '=' || ft_isdigit(s[i]))
		return (0);
	while (s[i] && s[i] != '=')
	{
			if (!ft_isalnum(s[i]) && s[i] != '_')
				return (0);
		i++;
	}
	return (i);
}

void		print_env(void)
{
	t_var_env *var_env;
	t_list		*tmp_env;

	tmp_env = g_env;
	while (tmp_env != NULL)
	{
		var_env = (t_var_env *)tmp_env->content;
		ft_putstr_fd(var_env->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(var_env->var, 1);
		tmp_env = tmp_env->next;
	}
}

t_var_env	*malloc_varenv(char *key, char *str)
{
	t_var_env	*ret;
	ret = (t_var_env *)malloc(sizeof(t_var_env));
	ret->key = key;
	ret->var = str;
	return (ret);
}

char	*get_env_var(char *search)
{
	t_var_env	*var_env;
	t_list		*tmp_env;
	size_t		len;

	tmp_env = g_env;
	print_env();
	var_env = (t_var_env *)tmp_env->content;
	if (ft_strlen(var_env->key) < ft_strlen(search))
		len = ft_strlen(search);
	else
		len = ft_strlen(var_env->key);
	while (ft_strncmp(var_env->key, search, len))
	{
		tmp_env = tmp_env->next;
		if (tmp_env == NULL)
			return (NULL);
		var_env = (t_var_env *)tmp_env->content;
	}
	return (var_env->var);
}

void	set_env_var(char *key, char* var)
{
	t_var_env	*var_env;
	t_list		*tmp_env;

	tmp_env = g_env;
	if (get_env_var(key) != NULL)
	{
		var_env = (t_var_env *)tmp_env->content;
		while (ft_strncmp(var_env->key, key, ft_strlen(var_env->key)))
		{
			tmp_env = tmp_env->next;
			var_env = (t_var_env *)tmp_env->content;
		}
		var_env->var = var;
	}
	else
		ft_lstadd_back(&tmp_env, ft_lstnew(malloc_varenv(key, var)));
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
			ret = ft_lstnew(malloc_varenv(envp[i], &c[1])); //malloc
		else
			ft_lstadd_back(&ret, ft_lstnew(malloc_varenv(envp[i], &c[1]))); //malloc
		i++;
	}
	return (ret);
}

char	**list_to_envp(void)
{
	int		len;
	int		i;
	char	**ret;

	len = ft_lstsize(g_env);
	ret = (char **)malloc(sizeof(char *) * (len + 1)); //malloc
	i = 0;
	while (g_env != NULL)
	{
		ret[i] = ft_strjoin_c(((t_var_env *)g_env->content)->key,
					((t_var_env *)g_env->content)->var, '='); //malloc
		g_env = g_env->next;
		i++;
	}
	ret[len] = NULL;
	return (ret);
}

void	dealloc_tab(char **tab)
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
