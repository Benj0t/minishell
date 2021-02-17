/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:50:56 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/17 15:35:22 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		save_arg(t_token *tok, t_managparse *manag, t_list **list)
{
	t_list	*tmp;

	if (environnment_expander(tok, manag) && backslash_remove(tok, manag)\
		&& expansion(tok, manag))
	{
		tmp = ft_lstnew(tok->name);
		if (tmp == NULL)
			malloc_fail(*tok, manag);
		ft_lstadd_back(list, tmp);
	}
	return (parser_token(manag));
}

int		test_arg(t_token *tok, t_managparse *manag, t_list **list)
{
	if (tok->type == tok_space || tok->type == tok_tab)
	{
		free(tok->name);
		*tok = next_token(manag);
	}
	if (tok->type > T_NOWORD)
		return (error_parser(EUNEXPECTED, tok->name));
	return (save_arg(tok, manag, list));
}

void	next_free_token(t_token *tok, t_managparse *manag)
{
	free(tok->name);
	*tok = next_token(manag);
}

int		save_tok_out(t_token *tok, t_managparse *manag)
{
	next_free_token(tok, manag);
	if (tok->type == tok_out)
	{
		next_free_token(tok, manag);
		return (test_arg(tok, manag, &manag->command->redir_append));
	}
	else
		return (test_arg(tok, manag, &manag->command->redir_out));
	return (parser_token(manag));
}

int		save_tok_in(t_token *tok, t_managparse *manag)
{
	next_free_token(tok, manag);
	return (test_arg(tok, manag, &manag->command->redir_in));
}

int		save_tok_pipe(t_token *tok, t_managparse *manag)
{
	free(tok->name);
	manag->command->pipe = setup_command();
	if (manag->command->pipe == NULL)
		malloc_fail(*tok, manag);
	return (parser_token(manag));
}

int		parser_token(t_managparse *manag)
{
	t_token		tok;
	t_list		*tmp;

	tok = next_token(manag);
	if (tok.type == tok_space || tok.type == tok_tab)
		next_free_token(&tok, manag);
	if (tok.type == tok_eof || tok.type == tok_end)
		return (0);
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
