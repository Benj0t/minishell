/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:40:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/22 17:17:53 by psemsari         ###   ########.fr       */
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
	while (s[i] && s[i] != '=' && s[i] != '+')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (i);
}

void		print_env(char	*prefix, t_list *env, int print_null)
{
	t_var_env	*var_env;
	t_list		*tmp_env;

	tmp_env = env;
	while (tmp_env != NULL)
	{
		var_env = (t_var_env *)tmp_env->content;
		if (var_env->var)
			printf("%s%s=%s\n", prefix, var_env->key, var_env->var);
		else if (!var_env->var && print_null)
			printf("%s%s\n", prefix, var_env->key);
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
