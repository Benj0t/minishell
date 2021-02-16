/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:50:56 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/16 19:45:12 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//- connaitre quels sont les tokens
//- associer un str à un token
//- expand
//- traiter le token (erreur ou un chemin - graph)

// exemple : cat <lol.c>> out;echo $yop "$yop" '$yop'

#include "minishell.h"
#include "token.h"

void	malloc_fail(t_token tok, t_managparse *manag)
{
	clear_multi_command(manag->command);
	ft_lstclear(&env, free);
	printf("malloc_failed\n");
	exit(1);
}

int		error_parser(char *str, char *name)
{
	if (str == NULL)
		printf("minishell: %s\n", name);
	else
		printf("minishell: %s `%s`\n", str, name);
	free(name);
	return (1);
}

int		parser_token(t_managparse *manag)
{
	t_token		tok;

	tok = next_token(manag);
	if (tok.type == tok_space || tok.type == tok_tab)
	{
		free(tok.name);
		tok = next_token(manag);
	}
	if (tok.type == tok_eof)
		return (0);
	if (tok.type > T_NOWORD && manag->command->argument == NULL)
		return (error_parser(EUNEXPECTED, tok.name));
	if (tok.type == tok_word)
	{
		if (environnment_expander(&tok, manag) && backslash_remove(&tok, manag) && expansion(&tok, manag))
			ft_lstadd_back(&manag->command->argument, ft_lstnew(tok.name)); //malloc
		return (parser_token(manag));
	}
	if (tok.type == tok_out)
	{
		free(tok.name);
		tok = next_token(manag);
		if (tok.type == tok_out)
		{
			free(tok.name);
			tok = next_token(manag);
			if (tok.type == tok_space || tok.type == tok_tab)
			{
				free(tok.name);
				tok = next_token(manag);
			}
			if (tok.type > T_NOWORD)
				return (error_parser(EUNEXPECTED, tok.name));
			if (environnment_expander(&tok, manag) && backslash_remove(&tok, manag) && expansion(&tok, manag))
				ft_lstadd_back(&manag->command->redir_append, ft_lstnew(tok.name)); //malloc
			return (parser_token(manag));
		}
		else
		{
			if (tok.type == tok_space || tok.type == tok_tab)
			{
				free(tok.name);
				tok = next_token(manag);
			}
			if (tok.type > T_NOWORD)
				return (error_parser(EUNEXPECTED, tok.name));
			if (environnment_expander(&tok, manag) && backslash_remove(&tok, manag) && expansion(&tok, manag))
				ft_lstadd_back(&manag->command->redir_out, ft_lstnew(tok.name)); //malloc
			return (parser_token(manag));
		}
	}
	if (tok.type == tok_in)
	{
		free(tok.name);
		tok = next_token(manag);
		if (tok.type == tok_space || tok.type == tok_tab)
		{
			free(tok.name);
			tok = next_token(manag);
		}
		if (tok.type > T_NOWORD)
			return (error_parser(EUNEXPECTED, tok.name));
		if (environnment_expander(&tok, manag) && backslash_remove(&tok, manag) && expansion(&tok, manag))
			ft_lstadd_back(&manag->command->redir_in, ft_lstnew(tok.name)); //malloc
		return (parser_token(manag));
	}
	if (tok.type == tok_pipe)
	{
		free(tok.name);
		manag->command->pipe = setup_command();
		return (parser_token(manag));
	}
	if (tok.type == tok_error)
		return (error_parser(NULL, tok.name));
	free(tok.name);
	return (parser_token(manag));
}
