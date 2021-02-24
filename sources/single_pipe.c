/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:19:06 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/24 12:25:28 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		pid_manager(t_pipe *spipe, int child[2])
{
	if (spipe->ret[0] == 1)
	{
		waitpid(child[0], (int *)&(spipe->pid[0]), 0);
		spipe->ret[0] = WEXITSTATUS(spipe->pid[0]);
	}
	if (spipe->ret[1] == 1)
	{
		waitpid(child[1], (int *)&(spipe->pid[1]), 0);
		spipe->ret[1] = WEXITSTATUS(spipe->pid[1]);
	}
}

static int	left_command(t_pipe *spipe, t_redir *redir,\
						t_command *command, int p[2])
{
	int			child;
	t_parser	comm1;

	if ((get_command(command->argument, &comm1)) == -1)
		free_struct(spipe, redir, command);
	if (init_path(spipe->l_env, comm1, spipe) == NULL)
		spipe->ret[0] = invalid_command(spipe, comm1);
	if (spipe->ret[0] == 1 && (child = fork()) == 0)
	{
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
	free(comm1.argument);
	return (child);
}

static int	right_command(t_pipe *spipe, t_redir *redir,\
						t_command *command, int p[2])
{
	int			child;
	t_parser	comm2;

	if ((get_command(command->pipe->argument, &comm2)) == -1)
		free_struct(spipe, redir, command);
	if (init_path(spipe->l_env, comm2, spipe) == NULL)
		spipe->ret[1] = invalid_command(spipe, comm2);
	if (spipe->ret[1] == 1 && (child = fork()) == 0)
	{
		if (redir->std_in == -1)
			dup2(p[0], 0);
		close(p[1]);
		execve(spipe->path, comm2.argument, spipe->l_env);
	}
	close(p[0]);
	close(p[1]);
	free(comm2.argument);
	spipe->index++;
	return (child);
}

void		check_builtin(t_pipe *spipe, t_redir *redir, t_command *command)
{
	if ((spipe->ret[1] = scan_builtins(command, spipe)) == 0)
	{
		if (redir->std_in == -1)
			dup2(spipe->curr_p[0], 0);
		spipe->ret[1] = builtins(command->pipe, spipe);
	}
}

int			single_pipe(t_command *command,\
					t_redir *redir, t_pipe *spipe)
{
	int			child[2];

	if (exec_redir(command, redir) == -1 || pipe(spipe->curr_p) < 0)
		return (-1);
	set_local_env(spipe);
	if ((spipe->ret[0] = scan_builtins(command, spipe)) == 0)
	{
		if (redir->std_in == -1 && redir->std_out == -1)
			dup2(spipe->curr_p[1], 1);
		builtins(command, spipe);
	}
	if ((child[0] = left_command(spipe, redir, command, spipe->curr_p)) == -1)
		return (0);
	end_redir(redir);
	set_local_env(spipe);
	if (exec_redir(command, redir) == -1)
		return (-1);
	check_builtin(spipe, redir, command);
	if ((child[1] = right_command(spipe, redir, command, spipe->curr_p)) == -1)
		return (0);
	end_redir(redir);
	pid_manager(spipe, child);
	return (1);
}
