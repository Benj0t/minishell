/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:50:56 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/14 17:33:39 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//- connaitre quels sont les tokens
//- associer un str à un token
//- expand
//- traiter le token (erreur ou un chemin - graph)

// exemple : cat <lol.c>> out;echo $yop "$yop" '$yop'

#include "minishell.h"
#include "token.h"

int		error_parser(char *str, char *name)
{
	printf("error: %s '%s'\n", str, name);
	return (1);
}

int		parser_token(char **str, t_command *command)
{
	t_token		tok;

	tok = next_token(str);
	while (tok.type == tok_space || tok.type == tok_tab)
		tok = next_token(str);
	if (tok.type == tok_eof)
		return (0);
	if (tok.type > T_NOWORD && command->argument == NULL)
		return (error_parser("unexpected token", tok.name));
	if (tok.type == tok_word)
		ft_lstadd_back(&command->argument, ft_lstnew(tok.name));
	if (tok.type == tok_out)
	{
		tok = next_token(str);
		if (tok.type == tok_out)
		{
			tok = next_token(str);
			while (tok.type == tok_space || tok.type == tok_tab)
				tok = next_token(str);
			if (tok.type > T_NOWORD)
				return (error_parser("unexpected token", tok.name));
			ft_lstadd_back(&command->redir_append, ft_lstnew(tok.name));
		}
		else
		{
			while (tok.type == tok_space || tok.type == tok_tab)
				tok = next_token(str);
			if (tok.type > T_NOWORD)
				return (error_parser("unexpected token", tok.name));
			ft_lstadd_back(&command->redir_out, ft_lstnew(tok.name));
		}
	}
	if (tok.type == tok_in)
	{
		tok = next_token(str);
		while (tok.type == tok_space || tok.type == tok_tab)
			tok = next_token(str);
		if (tok.type > T_NOWORD)
			return (error_parser("unexpected token", tok.name));
		ft_lstadd_back(&command->redir_in, ft_lstnew(tok.name));
	}
	if (tok.type == tok_pipe)
	{
		command->pipe = setup_command();
		return (parser_token(str, command->pipe));
	}
	if (tok.type == tok_end)
		return (0);
	return (parser_token(str, command));
}
