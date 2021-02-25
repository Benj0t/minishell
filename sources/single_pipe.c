/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:19:06 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/26 00:04:13 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_child;
extern int		g_signal_b;

void		pid_manager(t_pipe *spipe)
{
	if (spipe->ret[0] == 0)
	{
		waitpid(spipe->child[0], (int *)&(spipe->pid[0]), 0);
		spipe->ret[0] = WEXITSTATUS(spipe->pid[0]);
	}
	if (g_signal_b == 131)
	{
		spipe->ret[0] = 131;
		g_signal_b = 0;
	}
	if (spipe->ret[1] == 0)
	{
		waitpid(spipe->child[1], (int *)&(spipe->pid[1]), 0);
		spipe->ret[1] = WEXITSTATUS(spipe->pid[1]);
	}
	if (g_signal_b == 131)
	{
		spipe->ret[0] = 131;
		g_signal_b = 0;
	}
}

static int	left_command(t_pipe *spipe, t_redir *redir,\
						t_command *command)
{
	t_parser	comm1;

	if ((get_command(command->argument, &comm1)) == -1)
		free_struct(spipe, &comm1, command);
	if (init_path(spipe->l_env, comm1, spipe) == NULL && spipe->b_ret[spipe->index] == 1)
			return (spipe->ret[0] = invalid_command(spipe, &comm1));
	if ((g_child = fork()) == 0)
	{
		if (redir->std_in == -1 && redir->std_out == -1)
			dup2(spipe->curr_p[1], 1);
		close(spipe->curr_p[0]);
		if (spipe->b_ret[spipe->index] == 0)
			exit(builtins(command, spipe));
		else if (spipe->b_ret[spipe->index] == 1)
			execve(spipe->path, comm1.argument, spipe->l_env);
		if (redir->std_out != -1)
		{
			end_redir(redir);
			return (0);
		}
	}
	spipe->child[0] = g_child;
	free(comm1.argument);
	return (g_child);
}

static int	right_command(t_pipe *spipe, t_redir *redir,\
						t_command *command)
{
	t_parser	comm2;

	if ((get_command(command->pipe->argument, &comm2)) == -1)
		free_struct(spipe, &comm2, command);
	if (init_path(spipe->l_env, comm2, spipe) == NULL  && spipe->b_ret[spipe->index] == 1)
			return (spipe->ret[spipe->index] = invalid_command(spipe, &comm2));
	if ((g_child = fork()) == 0)
	{
		if (redir->std_in == -1)
			dup2(spipe->curr_p[0], 0);
		close(spipe->curr_p[1]);
		if (spipe->b_ret[spipe->index] == 0)
			exit(builtins(command->pipe, spipe));
		else if (spipe->b_ret[spipe->index] == 1)
			execve(spipe->path, comm2.argument, spipe->l_env);
	}
	spipe->child[1] = g_child;
	close(spipe->curr_p[0]);
	close(spipe->curr_p[1]);
	free(comm2.argument);
	free(spipe->path);
	return (g_child);
}

int			single_pipe(t_command *command,\
					t_redir *redir, t_pipe *spipe)
{

	if (exec_redir(command, redir) == -1 || pipe(spipe->curr_p) < 0)
		return (-1);
	set_local_env(spipe);
	spipe->b_ret[spipe->index] = scan_builtins(command, spipe);
	if ((left_command(spipe, redir, command)) == -1)
		return (0);
	end_redir(redir);
	set_local_env(spipe);
	if (exec_redir(command->pipe, redir) == -1)
		return (-1);
	spipe->b_ret[++spipe->index] = scan_builtins(command->pipe, spipe);

	if ((right_command(spipe, redir, command)) == -1)
		return (0);
	close(spipe->curr_p[0]);
	close(spipe->curr_p[1]);
	pid_manager(spipe);
	
	end_redir(redir);
	return (1);
}
