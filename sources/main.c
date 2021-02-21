/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:17:57 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/21 20:41:02 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipe.h"
#include "parser.h"

t_list	*g_env;

void	init_env(char **envp)
{
	char	*str;

	if (!envp)
	{
		g_env = NULL;
		return ;
	}
	g_env = envp_to_list(envp);
	if (!g_env)
		return (ft_lstclear(&g_env, free));
	str = get_env("SHLVL");
	if (!str)
		return (ft_lstclear(&g_env, free));
	str = ft_itoa(ft_atoi(str) + 1);
	set_env("SHLVL", str, 1);
	return ;
}

int		main(int ac, char **av, char **envp)
{
	char		*str;
	t_redir		redir;
	s_pipe		spipe;

	(void)ac;
	spipe.last_ret = 0;
	init_env(envp);
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
