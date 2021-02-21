/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:17:57 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/21 14:04:54 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipe.h"
#include "parser.h"

t_list	*g_env;

int		main(int ac, char **av, char **envp)
{
	char		*str;
	t_redir		redir;
	s_pipe		spipe;

	(void)ac;
	spipe.last_ret = 0;
	g_env = envp_to_list(envp);
	spipe.ret = 0;
	while (1)
	{
		ft_putstr_fd("> ", 2);
		gnl_prompt(0, &str, &spipe.last_ret);
		parser(&str, &redir, &spipe);
		free(str);
	}
	free(str);
	ft_lstclear(&g_env, free);
	return (0);
}
