/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:31:23 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/24 03:13:07 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_parser(char *str, char *name)
{
	ft_putstr_fd("minishell: ", 2);
	if (str != NULL)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" ", 2);
	}
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
	free(name);
	return (1);
}

void	malloc_fail(t_token tok, t_managparse *manag)
{
	clear_multi_command(manag->command);
	ft_lstclear(&g_env, &dealloc_varenv);
	printf("malloc_failed\n");
	exit(1);
}

t_redirection	*malloc_redirection(char *arg, int flag)
{
	t_redirection	*ret;

	ret = (t_redirection *)malloc(sizeof(t_redirection));
	if (ret == NULL)
		return (NULL);
	ret->arg = arg;
	ret->in = 0;
	ret->out = 0;
	ret->append = 0;
	if (flag == 1)
		ret->out = 1;
	else if (flag == 2)
		ret->append = 1;
	else
		ret->in = 1;
	return (ret);
}

void			dealloc_redirection(void *content)
{
	t_redirection	*malloc;

	malloc = (t_redirection *)content;
	free(malloc->arg);
	free(malloc);
}

int		save_arg(t_token *tok, t_managparse *manag, int flag)
{
	t_list	*tmp;

	if (environnment_expander(tok, manag) && backslash_remove(tok, manag)\
		&& expansion(tok, manag))
	{
		tmp = malloc_redirection(tok->name, flag);
		if (tmp == NULL)
			malloc_fail(*tok, manag);
		tmp = ft_lstnew(tmp);
		if (tmp == NULL)
			malloc_fail(*tok, manag);
		ft_lstadd_back(&manag->command->redirection, tmp);
	}
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

void	next_free_token(t_token *tok, t_managparse *manag)
{
	free(tok->name);
	*tok = next_token(manag);
	while (tok->type == tok_space || tok->type == tok_tab)
	{
		free(tok->name);
		*tok = next_token(manag);
	}
}
