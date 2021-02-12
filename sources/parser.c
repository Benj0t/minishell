/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:50:56 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/12 15:47:37 by psemsari         ###   ########.fr       */
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
	if (str == NULL)
		printf("minishell: %s\n", name);
	else
		printf("minishell: %s `%s`\n", str, name);
	free(name);
	return (1);
}

//probleme : quand il n'y a pas d'espace tout les elements sont un seul argument
int		parser_token(char **str, t_command *command, t_list *env, s_pipe *spipe)
{
	t_token		tok;

	tok = next_token(str);
	if (tok.type == tok_space || tok.type == tok_tab)
	{
		free(tok.name);
		tok = next_token(str);
	}
	if (tok.type == tok_eof)
		return (0);
	if (tok.type > T_NOWORD && command->argument == NULL)
		return (error_parser(EUNEXPECTED, tok.name));
	if (tok.type == tok_word)
	{
		if (environnment_expander(&tok, env, spipe) && backslash_remove(&tok) && expansion(&tok))
			ft_lstadd_back(&command->argument, ft_lstnew(tok.name));
	}
	if (tok.type == tok_out)
	{
		tok = next_token(str);
		if (tok.type == tok_out)
		{
			tok = next_token(str);
			if (tok.type == tok_space || tok.type == tok_tab)
				tok = next_token(str);
			if (tok.type > T_NOWORD)
				return (error_parser(EUNEXPECTED, tok.name));
			if (environnment_expander(&tok, env, spipe) && expansion(&tok))
				ft_lstadd_back(&command->redir_append, ft_lstnew(tok.name));
		}
		else
		{
			if (tok.type == tok_space || tok.type == tok_tab)
				tok = next_token(str);
			if (tok.type > T_NOWORD)
				return (error_parser(EUNEXPECTED, tok.name));
			if (environnment_expander(&tok, env, spipe) && expansion(&tok))
				ft_lstadd_back(&command->redir_out, ft_lstnew(tok.name));
		}
	}
	if (tok.type == tok_in)
	{
		tok = next_token(str);
		if (tok.type == tok_space || tok.type == tok_tab)
			tok = next_token(str);
		if (tok.type > T_NOWORD)
			return (error_parser(EUNEXPECTED, tok.name));
		if (environnment_expander(&tok, env, spipe) && expansion(&tok))
			ft_lstadd_back(&command->redir_in, ft_lstnew(tok.name));
	}
	if (tok.type == tok_pipe)
	{
		command->pipe = setup_command();
		return (parser_token(str, command->pipe, env, spipe));
	}
	if (tok.type == tok_end)
	{
		free(tok.name);
		return (0);
	}
	if (tok.type == tok_error)
		return (error_parser(NULL, tok.name));
	free(tok.name);
	return (parser_token(str, command, env, spipe));
}
