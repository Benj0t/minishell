/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:19:06 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/18 14:52:03 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		pid_manager(s_pipe *spipe, int child[2])
{
	if (spipe->ret[0] == -1)
	{
		waitpid(child[0], (int *)&(spipe->pid[0]), 0);
		spipe->ret[0] = WEXITSTATUS(spipe->pid[0]);
	}
	if (spipe->ret[1] == -1)
	{
		waitpid(child[1], (int *)&(spipe->pid[1]), 0);
		spipe->ret[1] = WEXITSTATUS(spipe->pid[1]);
	}
}

static int	left_command(s_pipe *spipe, t_redir *redir,\
						t_command *command, int p[2])
{
	int			child;
	t_parser	comm1;

	comm1 = get_command(command->argument);
	if (spipe->ret[0] == -1 && (child = fork()) == 0)
	{
		if (redir->std_in == -1 && redir->std_out == -1)
			dup2(p[1], 1);
		close(p[0]);
		execve(init_path(spipe->l_env, comm1, spipe),\
				comm1.argument, spipe->l_env);
		if (redir->std_out != -1)
		{
			end_redir(redir);
			return (0);
		}
	}
	end_redir(redir);
	return (child);
}

static int	right_command(s_pipe *spipe, t_redir *redir,\
						t_command *command, int p[2])
{
	int			child;
	t_parser	comm2;

	comm2 = get_command(command->pipe->argument);
	if (spipe->ret[1] == -1 && (child = fork()) == 0)
	{
		if (redir->std_in == -1)
			dup2(p[0], 0);
		close(p[1]);
		execve(init_path(spipe->l_env, comm2, spipe),\
				comm2.argument, spipe->l_env);
	}
	close(p[0]);
	close(p[1]);
	end_redir(redir);
	return (child);
}

int			single_pipe(t_command *command,\
					t_redir *redir, s_pipe *spipe)
{
	int			p[2];
	int			child[2];

	exec_redir(command, redir);
	if (pipe(p) < 0)
		return (-1);
	set_local_env(spipe);
	spipe->ret[0] = builtins(command, spipe);
	child[0] = left_command(spipe, redir, command, p);
	if (child[0] == -1)
		return (0);
	set_local_env(spipe);
	exec_redir(command->pipe, redir);
	spipe->ret[1] = builtins(command, spipe);
	child[1] = right_command(spipe, redir, command, p);
	if (child[1] == -1)
		return (0);
	pid_manager(spipe, child);
	return (1);
}
