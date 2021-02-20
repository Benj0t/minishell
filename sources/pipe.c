/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 16:30:54 by marvin            #+#    #+#             */
/*   Updated: 2021/02/20 06:42:13 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t g_child;

void	sig_quit(int sigid)
{
	if (sigid == SIGQUIT && g_child != 0)
	{
		write(1, "\n", 1);
		kill(g_child, SIGTERM);
	}
}

int		simple_command(t_list *env, t_command *cmd,\
						t_redir *redir, s_pipe *spipe)
{
	t_parser	comm1;
	int			ret;

	g_child = 0;
	comm1 = get_command(cmd->argument);
	set_local_env(env, spipe);
	if (exec_redir(cmd, redir) == -1)
		return (0);
	ret = builtins(cmd, env, spipe);
	if (ret == -1)
	{
		signal(SIGQUIT, &sig_quit);
		if ((g_child = fork()) == 0)
		{
			if (init_path(spipe->l_env, comm1, spipe) == NULL)
				invalid_command(spipe, comm1);
			execve(spipe->path, comm1.argument, spipe->l_env);
		}
		waitpid(g_child, (int *)&(spipe->pid[0]), 0);
		spipe->ret[0] = WEXITSTATUS(spipe->pid[0]);
	}
	end_redir(redir);
	return (ret);
}

int		ft_ret(int *ret)
{
	int i;

	i = 0;
	while (ret[i] != -1)
	{
		i++;
	}
	return ((unsigned char)ret[i - 1]);
}

int		execution(t_list *env, t_command *cmd, t_redir *redir, s_pipe *spipe)
{
	int i;
	int ret;

	i = 0;
	if (cmd->argument == NULL)
		return (-1);
	spipe->n_comm = listlen(cmd);
	if (!init_spipe(spipe))
		return (-1);
	if (spipe->n_comm == 1)
		simple_command(env, cmd, redir, spipe);
	else if (spipe->n_comm == 2)
	{
		single_pipe(env, cmd, redir, spipe);
	}
	else if (spipe->n_comm > 2)
	{
		multi_pipe(env, cmd, spipe, redir);
		spipe->index = 0;
	}
	spipe->last_ret = spipe->ret[spipe->index];
	//free_spipe(spipe);
	return (0);
}
