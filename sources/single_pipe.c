/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:19:06 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/20 06:13:53 by bemoreau         ###   ########.fr       */
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
		if (init_path(spipe->l_env, comm1, spipe) == NULL)
			invalid_command(spipe, comm1);
		if (redir->std_in == -1 && redir->std_out == -1)
			dup2(p[1], 1);
		close(p[0]);
		execve(spipe->path, comm1.argument, spipe->l_env);
		if (redir->std_out != -1)
		{
			end_redir(redir);
			return (0);
		}
	}
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
		if (init_path(spipe->l_env, comm2, spipe) == NULL)
			invalid_command(spipe, comm2);
		if (redir->std_in == -1)
			dup2(p[0], 0);
		close(p[1]);
		execve(spipe->path, comm2.argument, spipe->l_env);
	}
	close(p[0]);
	close(p[1]);
	spipe->index++;
	return (child);
}

void		check_builtin(s_pipe *spipe, t_redir *redir, t_command *command)
{
	if ((spipe->ret[1] = scan_builtins(command, env, spipe)) == 1)
	{
		if (redir->std_in == -1)
			dup2(spipe->curr_p[0], 0);
		spipe->ret[1] = builtins(command->pipe, env, spipe);
	}
}

int			single_pipe(t_list *env, t_command *command,\
					t_redir *redir, s_pipe *spipe)
{
	int			child[2];

	if (exec_redir(command, redir) == -1 || pipe(spipe->curr_p) < 0)
		return (-1);
	set_local_env(env, spipe);
	if ((spipe->ret[0] = scan_builtins(command, env, spipe)) == 1)
	{
		if (redir->std_in == -1 && redir->std_out == -1)
			dup2(spipe->curr_p[1], 1);
		builtins(command, env, spipe);
	}
	if ((child[0] = left_command(spipe, redir, command, spipe->curr_p)) == -1)
		return (0);
	end_redir(redir);
	set_local_env(env, spipe);
	if (exec_redir(command, redir) == -1)
		return (-1);
	check_builtin(spipe, redir, command);
	if ((child[1] = right_command(spipe, redir, command, spipe->curr_p)) == -1)
		return (0);
	end_redir(redir);
	pid_manager(spipe, child);
	return (1);
}
