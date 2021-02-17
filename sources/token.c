/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:43:34 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/17 11:54:11 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

void			malloc_fail(t_token tok, t_managparse *manag)
{
	clear_multi_command(manag->command);
	ft_lstclear(&env, free);
	printf("malloc_failed\n");
	exit(1);
}

static char		in_list(char c, char *str)
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
	return (i + 1);
}

int				is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int				is_backslash(char *str, size_t i)
{
	if ((str[i + 1] == '\\' && (str[i] != ' ' && str[i] != '	'))\
		|| (i > 0 && str[i - 1] == '\\'))
	{
		if (backslash(str, i - 1))
			return (0);
		return (1);
	}
	return (0);
}

t_token			next_token(t_managparse *manag)
{
	t_token	tok;
	size_t	i;
	char	*tmp;
	char	quote;

	i = 0;
	tok.name = NULL;
	tok.type = tok_eof;
	if (manag->str[i] == '\0')
		return (tok);
	while ((!in_list(manag->str[i], T_ALL) && manag->str[i] != '\0')\
			|| is_backslash(manag->str, i))
	{
		if (is_quote(manag->str[i]) && !backslash(manag->str, i))
		{
			quote = manag->str[i];
			i++;
			while (manag->str[i] != '\0')
			{
				if (manag->str[i] == quote)
					if (!backslash(manag->str, i))
						break ;
				i++;
			}
			if (manag->str[i] == '\0')
			{
				tok.name = ft_strdup(&quote);
				if (tok.name == NULL)
					malloc_fail(tok, manag);
				tok.type = tok_error;
				return (tok);
			}
		}
		i++;
	}
	if (in_list(manag->str[i], T_ALL) && i == 0)
	{
		tok.name = ft_substr(manag->str, 0, 1);
		if (tok.name == NULL)
			malloc_fail(tok, manag);
		tok.type = search_type(*tok.name);
		tmp = ft_strdup(&manag->str[1]);
		if (tmp == NULL)
			malloc_fail(tok, manag);
		free(manag->str);
		manag->str = tmp;
		return (tok);
	}
	tok.type = tok_word;
	tok.name = ft_substr(manag->str, 0, i);
	if (tok.name == NULL)
		malloc_fail(tok, manag);
	tmp = ft_strdup(&manag->str[i]);
	if (tmp == NULL)
		malloc_fail(tok, manag);
	free(manag->str);
	manag->str = tmp;
	return (tok);
}
