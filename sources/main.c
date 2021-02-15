/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:17:57 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/15 15:47:00 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipe.h"
#include "parser.h"

t_list		*env;

int main(int ac, char **av, char **envp)
{
	char		*str;
	t_redir		redir;
	s_pipe		spipe;

	(void)ac;
	spipe.last_ret = 0;
	env = envp_to_list(envp);
	set_env_var("lol", "hey", env);
	spipe.ret = 0;
	while (1)
	{
		ft_putstr_fd("> ", 2);
		gnl_prompt(0, &str, &spipe.last_ret);
		parser(&str, &redir, &spipe);
		free(str);
	}
	free(str);
	ft_lstclear(&env, free);
	return (0);
}
