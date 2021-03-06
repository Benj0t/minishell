/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:17:57 by bemoreau          #+#    #+#             */
/*   Updated: 2021/03/01 00:38:55 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_env;
pid_t	g_child;

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
		return (ft_lstclear(&g_env, dealloc_varenv));
	str = get_env("SHLVL");
	if (!str)
		return ;
	str = ft_itoa(ft_atoi(str) + 1);
	set_env("SHLVL", str, 1);
	free(str);
	return ;
}

int		main(int ac, char **av, char **envp)
{
	char		*str;
	t_redir		redir;
	t_pipe		spipe;

	(void)ac;
	(void)av;
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
	return (0);
}
