/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:17:57 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/12 22:42:22 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipe.h"
#include "parser.h"

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_redir		redir;
	t_list		*env;
	s_pipe		spipe;
	int			pid;

	(void)ac;
	pid = 0;
	spipe.last_ret = 0;
	env = envp_to_list(envp);
	set_env_var("lol", "hey", env);
	spipe.ret = 0;
	while (1)
	{
		ft_putstr_fd("> ", 2);
		gnl_prompt(0, &str, &spipe.last_ret);
		parser(str, env, &redir, &spipe);
		free(str);
	}
	free(str);
	ft_lstclear(&env, free);
	return (0);
}
