/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:43:34 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/18 12:39:13 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static char	in_list(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return ((int)*str);
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

t_token		view_next_token(const char *str)
{
	t_token	tok;
	size_t	i;

	i = 0;
	tok.name = NULL;
	tok.type = tok_eof;
	if (str[i] == '\0')
	{
		str = NULL;
		return (tok);
	}
	while (!in_list(str[i], T_ALL))
		i++;
	if (in_list(str[i], T_ALL) && i == 0)
	{
		tok.name = ft_substr(str, 0, 1);
		tok.type = search_type(*tok.name);
		return (tok);
	}
	tok.type = tok_word;
	tok.name = ft_substr(str, 0, i);
	return (tok);
}

t_token		next_token(char **str)
{
	t_token	tok;
	size_t	i;

	i = 0;
	tok.name = NULL;
	tok.type = tok_eof;
	if (str[0][i] == '\0')
		return (tok);
	while (!in_list(str[0][i], T_ALL) && str[0][i] != '\0')
		i++;
	if (in_list(str[0][i], T_ALL) && i == 0)
	{
		tok.name = ft_substr(*str, 0, 1);
		tok.type = search_type(*tok.name);
		*str = ft_strdup(&str[0][1]); //free
		// printf("-%s-%d\n", tok.name, tok.type);
		return (tok);
	}
	tok.type = tok_word;
	tok.name = ft_substr(*str, 0, i);
	*str = ft_strdup(&str[0][i]); //free
	// printf("-%s-%d\n", tok.name, tok.type);
	return (tok);
}

