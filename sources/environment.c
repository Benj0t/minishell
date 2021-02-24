/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:40:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/24 12:24:49 by bemoreau         ###   ########.fr       */
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
				break ;
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
	while (s[i] && s[i] != '=' && s[i] != '+')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (i);
}

void		print_env(char *prefix, t_list *env)
{
	t_var_env	*var_env;
	t_list		*tmp_env;

	tmp_env = env;
	while (tmp_env != NULL)
	{
		var_env = (t_var_env *)tmp_env->content;
		if (var_env->var)
		{
			ft_putstr_fd(prefix, 1);
			ft_putstr_fd(var_env->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(var_env->var, 1);
			ft_putchar_fd('\n', 1);
		}
		tmp_env = tmp_env->next;
	}
}

t_var_env	*malloc_varenv(const char *key, const char *str)
{
	t_var_env	*ret;

	ret = (t_var_env *)malloc(sizeof(t_var_env));
	ret->var = NULL;
	ret->key = ft_strdup(key);
	if (str != NULL)
		ret->var = ft_strdup(str);
	return (ret);
}

void		dealloc_varenv(void *content)
{
	t_var_env *var_env;

	var_env = (t_var_env *)content;
	free(var_env->key);
	if (var_env->var != NULL)
		free(var_env->var);
	free(var_env);
}
