/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:43:34 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/12 15:17:28 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static char	in_list(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static t_ttoken	search_type(char c)
{
	int		i;

	i = 0;
	while (T_ALL[i] != c)
		i++;
	return (i+1);
}

int			is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int			is_backslash(char *str, size_t i)
{
	if ((str[i + 1] == '\\' && (str[i] != ' ' && str[i] != '	')) || str[i - 1] == '\\')
	{
		if (backslash(str, i - 1))
			return (0);
		return (1);
	}
	return (0);
}

t_token		next_token(char **str)
{
	t_token	tok;
	size_t	i;
	char	*tmp;
	char	quote;

	i = 0;
	tok.name = NULL;
	tok.type = tok_eof;
	if (str[0][i] == '\0')
		return (tok);
	while ((!in_list(str[0][i], T_ALL) && str[0][i] != '\0') || is_backslash(str[0], i))
	{
		if (is_quote(str[0][i]) && !backslash(str[0], i))
		{
			quote = str[0][i];
			i++;
			while (str[0][i] != '\0')
			{
				if (str[0][i] == quote)
					if (!backslash(str[0], i))
						break;
				i++;
			}
			if (str[0][i] == '\0')
			{
				tok.name = ft_strdup(&quote);
				tok.type = tok_error;
				return (tok);
			}
		}
		i++;
	}
	if (in_list(str[0][i], T_ALL) && i == 0)
	{
		tok.name = ft_substr(*str, 0, 1);
		tok.type = search_type(*tok.name);
		tmp = ft_strdup(&str[0][1]);
		free(*str);
		*str = tmp;
		return (tok);
	}
	tok.type = tok_word;
	tok.name = ft_substr(*str, 0, i);
	tmp = ft_strdup(&str[0][i]);
	free(*str);
	*str = tmp;
	return (tok);
}
