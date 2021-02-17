/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:50:56 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/17 13:11:23 by psemsari         ###   ########.fr       */
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

int		parser_token(t_managparse *manag)
{
	t_token		tok;
	t_list		*tmp;

	tok = next_token(manag);
	if (tok.type == tok_space || tok.type == tok_tab)
	{
		free(tok.name);
		tok = next_token(manag);
	}
	if (tok.type == tok_eof || tok.type == tok_end)
		return (0);
	if (tok.type > T_NOWORD && manag->command->argument == NULL)
		return (error_parser(EUNEXPECTED, tok.name));
	if (tok.type == tok_word)
	{
		if (environnment_expander(&tok, manag) && backslash_remove(&tok, manag)\
			&& expansion(&tok, manag))
		{
			tmp = ft_lstnew(tok.name);
			if (tmp == NULL)
				malloc_fail(tok, manag);
			ft_lstadd_back(&manag->command->argument, tmp);
		}
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
			if (environnment_expander(&tok, manag) \
				&& backslash_remove(&tok, manag) && expansion(&tok, manag))
			{
				tmp = ft_lstnew(tok.name);
				if (tmp == NULL)
					malloc_fail(tok, manag);
				ft_lstadd_back(&manag->command->redir_append, tmp);
			}
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
			if (environnment_expander(&tok, manag) \
				&& backslash_remove(&tok, manag) && expansion(&tok, manag))
			{
				tmp = ft_lstnew(tok.name);
				if (tmp == NULL)
					malloc_fail(tok, manag);
				ft_lstadd_back(&manag->command->redir_out, tmp);
			}
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
		if (environnment_expander(&tok, manag) \
			&& backslash_remove(&tok, manag) && expansion(&tok, manag))
		{
			tmp = ft_lstnew(tok.name);
			if (tmp == NULL)
				malloc_fail(tok, manag);
			ft_lstadd_back(&manag->command->redir_in, tmp);
		}
		return (parser_token(manag));
	}
	if (tok.type == tok_pipe)
	{
		free(tok.name);
		manag->command->pipe = setup_command();
		if (manag->command->pipe == NULL)
			malloc_fail(tok, manag);
		return (parser_token(manag));
	}
	if (tok.type == tok_error)
		return (error_parser(NULL, tok.name));
	free(tok.name);
	return (parser_token(manag));
}
