/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:52:02 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/26 23:55:51 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		save_tok_append(t_token *tok, t_managparse *manag)
{
	if (tok->type == tok_end || tok->type == tok_in\
	|| tok->type == tok_out || tok->type == tok_pipe)
		error_parser(EUNEXPECTED, tok->name);
	if (tok->type == tok_space || tok->type == tok_space)
		next_free_token(tok, manag);
	if (tok->type == tok_word)
		return (test_arg(tok, manag, 1));
	else
	{
		tok->type = tok_error;
		return (error_parser(EUNEXPECTED, tok->name));
	}
	return (parser_token(manag));
}

int		save_tok_out(t_token *tok, t_managparse *manag)
{
	free(tok->name);
	*tok = next_token(manag);
	if (tok->type == tok_out)
	{
		next_free_token(tok, manag);
		if (tok->type == tok_end || tok->type == tok_in\
			|| tok->type == tok_out || tok->type == tok_pipe)
			error_parser(EUNEXPECTED, tok->name);
		if (tok->type == tok_word)
			return (test_arg(tok, manag, 2));
		else
		{
			tok->type = tok_error;
			return (error_parser(EUNEXPECTED, tok->name));
		}
	}
	else
		return (save_tok_append(tok, manag));
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

int		test_arg(t_token *tok, t_managparse *manag, int flag)
{
	if (tok->type == tok_space || tok->type == tok_tab)
	{
		free(tok->name);
		*tok = next_token(manag);
	}
	if (tok->type > T_NOWORD)
		return (error_parser(EUNEXPECTED, tok->name));
	return (save_arg(tok, manag, flag));
}
