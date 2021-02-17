/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:43:34 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/17 16:28:53 by psemsari         ###   ########.fr       */
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

t_token			word_tok(t_managparse *manag, size_t i)
{
	t_token	tok;
	char	*tmp;

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

t_token			others_tok(t_managparse *manag)
{
	t_token	tok;
	char	*tmp;

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

t_token			error_quote(t_managparse *manag, char quote)
{
	t_token	tok;

	tok.name = ft_strdup(&quote);
	if (tok.name == NULL)
		malloc_fail(tok, manag);
	tok.type = tok_error;
	return (tok);
}

size_t			quote_pass(t_managparse *manag, size_t i, char quote)
{
	i++;
	while (manag->str[i] != '\0')
	{
		if (manag->str[i] == quote)
			if (!backslash(manag->str, i))
				break ;
		i++;
	}
	return (i);
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
			i = quote_pass(manag, i, quote);
			if (manag->str[i] == '\0')
				return (error_quote(manag, quote));
		}
		i++;
	}
	if (in_list(manag->str[i], T_ALL) && i == 0)
		return (others_tok(manag));
	return (word_tok(manag, i));
}
