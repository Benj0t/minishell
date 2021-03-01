/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:31:23 by psemsari          #+#    #+#             */
/*   Updated: 2021/03/01 00:44:57 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				error_parser(char *str, char *name)
{
	ft_putstr_fd("minishell: ", 2);
	if (str != NULL)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" ", 2);
	}
	if (name != NULL)
	{
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(name, 2);
		ft_putchar_fd('\'', 2);
		free(name);
	}
	ft_putchar_fd('\n', 2);
	return (1);
}

void			malloc_fail(t_token tok, t_managparse *manag)
{
	(void)tok;
	clear_multi_command(manag->command);
	ft_lstclear(&g_env, &dealloc_varenv);
	ft_putstr_fd("malloc_failed\n", 2);
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
	else if (flag == 0)
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

void			next_free_token(t_token *tok, t_managparse *manag)
{
	free(tok->name);
	*tok = next_token(manag);
	while (tok->type == tok_space || tok->type == tok_tab)
	{
		free(tok->name);
		*tok = next_token(manag);
	}
}
