/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:50:56 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/12 16:47:34 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//- connaitre quels sont les tokens
//- associer un str à un token
//- expand
//- traiter le token (erreur ou un chemin - graph)

// exemple : cat <lol.c>> out;echo $yop "$yop" '$yop'

#include "minishell.h"
#include "token.h"

void	init_command(t_command *command)
{
	command->argument = NULL;
	command->pipe = NULL;
	command->redir_append = NULL;
	command->redir_in = NULL;
	command->redir_out = NULL;
}

void	error_parser(char *str, char *name)
{
	printf("error: %s '%s'\n", str, name);
	exit(0);
}

void	expander(t_ttoken *tok)
{
	if ()

}

void	parser_token(char **str, t_command *command)
{
	t_token	tok;
	t_token	tmp;

	tok = next_token(str);
	while (tok.type == tok_space || tok.type == tok_tab)
		tok = next_token(str);
	if (tok.type > 5 && command->argument == NULL)
		error_parser("unexpected token", tok.name);
	if (tok.type == tok_word)
	{
		ft_lstadd_back(&command->argument, ft_lstnew(tok.name));
		parser_token(str, command);
	}
	if (tok.type == tok_out)
	{
		tok = next_token(str);
		if (tok.type == tok_out)
		{
			tok = next_token(str);
			while (tok.type == tok_space || tok.type == tok_tab)
				tok = next_token(str);
			if (tok.type > 5)
				error_parser("unexpected token", tok.name);
			ft_lstadd_back(&command->redir_append, ft_lstnew(tok.name));
		}
		while (tok.type == tok_space || tok.type == tok_tab)
			tok = next_token(str);
		if (tok.type > 5)
			error_parser("unexpected token", tok.name);
		ft_lstadd_back(&command->redir_out, ft_lstnew(tok.name));
	}
	if (tok.type == tok_in)
	{
		tok = next_token(str);
		while (tok.type == tok_space || tok.type == tok_tab)
			tok = next_token(str);
		if (tok.type > 5)
			error_parser("unexpected token", tok.name);
		ft_lstadd_back(&command->redir_in, ft_lstnew(tok.name));
	}
	if (tok.type == tok_pipe)
	{
		init_command(command->pipe);
		parser_token(str, command->pipe);
	}
}
