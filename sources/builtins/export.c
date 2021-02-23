/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:34:02 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/23 14:56:27 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		print_env("declare -x ", copy, 1);
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
