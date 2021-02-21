/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:31:23 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/18 15:06:31 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_parser(char *str, char *name)
{
	if (str == NULL)
		printf("minishell: %s\n", name);
	else
		printf("minishell: %s `%s`\n", str, name);
	free(name);
	return (1);
}

void	malloc_fail(t_token tok, t_managparse *manag)
{
	clear_multi_command(manag->command);
	ft_lstclear(&g_env, free);
	printf("malloc_failed\n");
	exit(1);
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
