/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:50:56 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/24 02:53:29 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		save_tok_out(t_token *tok, t_managparse *manag)
{
	next_free_token(tok, manag);
	if (tok->type == tok_out)
	{
		next_free_token(tok, manag);
		if (tok->type == tok_word)
			return (test_arg(tok, manag, 2));
		else
		{
			tok->type = tok_error;
			return (error_parser(EUNEXPECTED, tok->name));
		}
	}
	else
	{
		if (tok->type == tok_space || tok->type == tok_space)
			next_free_token(tok, manag);
		if (tok->type == tok_word)
			return (test_arg(tok, manag, 1));
		else
		{
			tok->type = tok_error;
			return (error_parser(EUNEXPECTED, tok->name));
		}
	}
	return (parser_token(manag));
}

int		save_tok_in(t_token *tok, t_managparse *manag)
{
	next_free_token(tok, manag);
	if (tok->type == tok_word)
		return (test_arg(tok, manag, 0));
	else
	{
		tok->type = tok_error;
		return (error_parser(EUNEXPECTED, tok->name));
	}
}

int		save_tok_pipe(t_token *tok, t_managparse *manag)
{
	free(tok->name);
	manag->command->pipe = setup_command();
	if (manag->command->pipe == NULL)
		malloc_fail(*tok, manag);
	manag->command = manag->command->pipe;
	return (parser_token(manag));
}

int		free_ret(t_token *tok, t_managparse *manag)
{
	size_t	i;

	i = 0;
	while (manag->str[i] != '\0' && (manag->str[i] == ' ' || manag->str[i] == ';'))
	{
		if (manag->str[i] == ';')
			return (error_parser("syntax error near unexpected token", tok->name));
		i++;
	}
	free(tok->name);
	return (0);
}

int		parser_token(t_managparse *manag)
{
	t_token		tok;
	t_list		*tmp;

	tok = next_token(manag);
	if (tok.type == tok_space || tok.type == tok_tab)
		next_free_token(&tok, manag);
	if (tok.type == tok_eof || tok.type == tok_end)
		return (free_ret(&tok, manag));
	if (tok.type > T_NOWORD && manag->command->argument == NULL)
		return (error_parser(EUNEXPECTED, tok.name));
	if (tok.type == tok_word)
		return (save_arg(&tok, manag, &manag->command->argument));
	if (tok.type == tok_out)
		return (save_tok_out(&tok, manag));
	if (tok.type == tok_in)
		return (save_tok_in(&tok, manag));
	if (tok.type == tok_pipe)
		return (save_tok_pipe(&tok, manag));
	if (tok.type == tok_error)
		return (error_parser(NULL, tok.name));
	free(tok.name);
	return (parser_token(manag));
}
