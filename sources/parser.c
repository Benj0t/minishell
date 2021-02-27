/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:50:56 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/27 14:18:38 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_ret(t_token *tok, t_managparse *manag)
{
	size_t	i;

	i = 0;
	while (manag->str[i] != '\0' && \
		(manag->str[i] == ' ' || manag->str[i] == ';'))
	{
		if (manag->str[i] == ';')
			return (error_parser(EUNEXPECTED, tok->name));
		i++;
	}
	free(tok->name);
	return (0);
}

int		save_arg(t_token *tok, t_managparse *manag, int flag)
{
	t_list			*tmp;
	int				ret_expan;
	t_redirection	*redir;

	ret_expan = expansion(tok, manag);
	if (flag < 4 && tok->name == NULL)
		return (error_parser("ambiguous redirect", NULL));
	if (flag < 4)
	{
		redir = malloc_redirection(tok->name, flag);
		if (redir == NULL)
			malloc_fail(*tok, manag);
		tmp = ft_lstnew(redir);
	}
	else
		tmp = ft_lstnew(tok->name);
	if (tmp == NULL)
		malloc_fail(*tok, manag);
	if (flag < 4)
		ft_lstadd_back(&manag->command->redirection, tmp);
	else
		ft_lstadd_back(&manag->command->argument, tmp);
	return (parser_token(manag));
}

int		parser_token_way(t_token *tok, t_managparse *manag)
{
	if (tok->type == tok_end)
		return (free_ret(tok, manag));
	if (tok->type == tok_word)
		return (save_arg(tok, manag, 4));
	if (tok->type == tok_out)
		return (save_tok_out(tok, manag));
	if (tok->type == tok_in)
		return (save_tok_in(tok, manag));
	if (tok->type == tok_pipe)
		return (save_tok_pipe(tok, manag));
	if (tok->type == tok_error)
		return (error_parser(NULL, tok->name));
	free(tok->name);
	return (parser_token(manag));
}

int		parser_token(t_managparse *manag)
{
	t_token		tok;
	t_list		*tmp;

	tok = next_token(manag);
	if (tok.type == tok_space || tok.type == tok_tab)
		next_free_token(&tok, manag);
	if (tok.type == tok_eof)
		return (free_ret(&tok, manag));
	if (tok.type > T_NOWORD && manag->command->argument == NULL
		&& manag->command->redirection == NULL)
		return (error_parser(EUNEXPECTED, tok.name));
	return (parser_token_way(&tok, manag));
}
