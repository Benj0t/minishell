/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:04:28 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/24 12:30:53 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			in_list(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

t_ttoken		search_type(char c)
{
	int		i;

	i = 0;
	while (T_ALL[i] != c)
		i++;
	return (i + 1);
}

int				is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int				backslash(char *str, size_t i)
{
	if (i > 0 && str[i - 1] == '\\')
	{
		if (backslash(str, i - 1))
			return (0);
		return (1);
	}
	return (0);
}

int				is_backslash(char *str, size_t i)
{
	if (i < 0)
	{
		if ((str[i + 1] == '\\' && (str[i] != ' ' && str[i] != '	'))\
			|| str[i - 1] == '\\')
		{
			if (backslash(str, i - 1))
				return (0);
			return (1);
		}
	}
	return (0);
}
