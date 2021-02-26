/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:34:02 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/26 11:12:30 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_exportable(char *arg)
{
	int i;
	int j;
	char *s;

	s = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNIPQRSTUVWXYZ0123456789_";
	i = -1;
	j = 0;
	while (arg[++i])
	{
		while(s[j])
		{
			if (s[j++] != arg[i])
				return(1);
		}
		j = 0;
		i++;
	}
	return (0);
}

int		is_valid_env(char *s)
{
	size_t i;

	i = 0;
	if (s[i] == '=' || ft_isdigit(s[i]))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			if (s[i] != '+' || (s[i] == '+' && s[i + 1] != '='))
				return (0);
		}
		i++;
	}
	return (i);
}

int		invalid_id(char *arg)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(" : not a valid identifier\n", 2);
	return (1);
}

void		print_export(char *prefix, t_list *env)
{
	t_var_env	*var_env;
	t_list		*tmp_env;

	tmp_env = env;
	while (tmp_env != NULL)
	{
		var_env = (t_var_env *)tmp_env->content;
		ft_putstr_fd(prefix, 1);
		ft_putstr_fd(var_env->key, 1);
		if (var_env->var)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(var_env->var, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		tmp_env = tmp_env->next;
	}
}

int		ft_export(char **arg)
{
	t_list *copy;

	arg++;
	if (*arg == NULL)
	{
		copy = ft_lstcopy(g_env);
		if (copy == NULL)
			return (1);
		bubble_sort(copy);
		print_export("declare -x ", copy);
		ft_lstclear(&copy, NULL);
		return (0);
	}
	while (*arg != NULL)
	{
		if (!is_valid_env(*arg))
			return (invalid_id(*arg));
		put_env(*arg);
		arg++;
	}
	return (0);
}
