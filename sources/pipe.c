/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 16:30:54 by marvin            #+#    #+#             */
/*   Updated: 2021/02/24 01:13:19 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t g_child;

void	sig_quit(int sigid)
{
	if (sigid == SIGQUIT && g_child != 0)
	{
		write(1, "\n", 2);
		kill(g_child, SIGTERM);
	}
}

int		simple_command(t_command *cmd,\
						t_redir *redir, s_pipe *spipe)
{
	t_parser	comm1;
	int			ret;

	g_child = 0;
	if ((get_command(cmd->argument, &comm1)) == -1)
		free_struct(spipe, redir, cmd);
	set_local_env(spipe);
	if (exec_redir(cmd, redir) == -1)
		return (0);
	if ((scan_builtins(cmd, spipe)) == 0)
		spipe->ret[0] = builtins(cmd, spipe);
	else
	{
		signal(SIGQUIT, &sig_quit);
		if (init_path(spipe->l_env, comm1, spipe) == NULL)
			spipe->ret[0] = invalid_command(spipe, comm1);
		else 
		{
			if ((g_child = fork()) == 0)
				execve(spipe->path, comm1.argument, spipe->l_env);
			waitpid(g_child, (int *)&(spipe->pid[0]), 0);
			spipe->ret[0] = WEXITSTATUS(spipe->pid[0]);
		}
	}
	end_redir(redir);
	if (spipe->path)
		free(spipe->path);
	free(comm1.argument);
	return (spipe->ret[0]);
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

int		execution(t_command *cmd, t_redir *redir, s_pipe *spipe)
{
	int i;
	int ret;

	i = 0;
	if (cmd->argument == NULL)
		return (-1);
	spipe->n_comm = listlen(cmd);
	spipe->n_bin = spipe->n_comm - 1;
	if (!init_spipe(spipe))
		return (-1);
	if (spipe->n_comm == 1)
		simple_command(cmd, redir, spipe);
	else if (spipe->n_comm == 2)
	{
		single_pipe(cmd, redir, spipe);
	}
	else if (spipe->n_comm > 2)
	{
		multi_pipe(cmd, spipe, redir);
		spipe->index--;
	}
	spipe->last_ret = spipe->ret[spipe->index];
	free_spipe(spipe);
	return (0);
}
