/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:19:06 by bemoreau          #+#    #+#             */
/*   Updated: 2021/03/01 00:05:57 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_child;
extern int		g_signal_b;
extern int		g_signal_c;

static int		left_command(t_pipe *spipe, t_redir *redir,\
						t_command *command, t_parser comm)
{
	int index;

	index = spipe->b_ret[spipe->index];
	if (index && (init_path(spipe->l_env, comm, spipe) == NULL))
		return (spipe->ret[0] = invalid_command(spipe, &comm));
	if ((g_child = fork()) == 0)
	{
		if (redir->std_out == -1)
			dup2(spipe->curr_p[1], 1);
		close(spipe->curr_p[0]);
		if (spipe->b_ret[spipe->index] == 0)
			exit(builtins(command, spipe, &comm));
		else if (spipe->b_ret[spipe->index] == 1)
			exit(execve(spipe->path, comm.argument, spipe->l_env));
	}
	end_redir(redir);
	spipe->child[0] = g_child;
	free(comm.argument);
	return (0);
}

static int		right_command(t_pipe *spipe, t_redir *redir,\
						t_command *command, t_parser comm)
{
	int index;

	index = spipe->b_ret[spipe->index];
	if (index && (init_path(spipe->l_env, comm, spipe)) == NULL)
		return (spipe->ret[spipe->index] = invalid_command(spipe, &comm));
	if ((g_child = fork()) == 0)
	{
		if (redir->std_in == -1)
			dup2(spipe->curr_p[0], 0);
		close(spipe->curr_p[1]);
		if (spipe->b_ret[spipe->index] == 0)
			exit(builtins(command, spipe, &comm));
		else if (spipe->b_ret[spipe->index] == 1)
			execve(spipe->path, comm.argument, spipe->l_env);
	}
	spipe->child[1] = g_child;
	end_redir(redir);
	close(spipe->curr_p[0]);
	close(spipe->curr_p[1]);
	free(spipe->path);
	return (0);
}

int				left_pipe(t_command *command, t_redir *redir, t_pipe *spipe)
{
	t_parser comm;

	if (exec_redir(command, redir, spipe) == -1 || pipe(spipe->curr_p) < 0)
		return (-1);
	if ((get_command(command->argument, &comm)) == -1)
		return (-1);
	set_local_env(spipe);
	spipe->b_ret[spipe->index] = scan_builtins(command, spipe, &comm);
	if ((left_command(spipe, redir, command, comm)) != 0)
		return (0);
	return (1);
}

int				right_pipe(t_command *command, t_redir *redir, t_pipe *spipe)
{
	t_parser comm;

	if (spipe->curr_p[0] == -1 || spipe->curr_p[1] == -1)
		if (pipe(spipe->curr_p) < 0)
			return (0);
	if (exec_redir(command, redir, spipe) == -1)
		return (-1);
	if ((get_command(command->argument, &comm)) == -1)
		return (-1);
	set_local_env(spipe);
	spipe->b_ret[++spipe->index] = scan_builtins(command, spipe, &comm);
	if ((right_command(spipe, redir, command, comm)) != 0)
		return (0);
	if (spipe->ret[spipe->index] <= 1)
		free(comm.argument);
	return (1);
}

int				single_pipe(t_command *command, t_redir *redir, t_pipe *spipe)
{
	int			i;
	t_command	*tmp;

	tmp = command;
	i = 0;
	spipe->curr_p[0] = -1;
	spipe->curr_p[1] = -1;
	spipe->index = 0;
	while (i <= 1)
	{
		if ((tmp->argument == NULL || tmp->argument->content == NULL))
		{
			exec_redir(tmp, redir, spipe);
			end_redir(redir);
		}
		else if (i == 0)
			left_pipe(tmp, redir, spipe);
		else if (i == 1)
			right_pipe(tmp, redir, spipe);
		tmp = tmp->pipe;
		i++;
	}
	pid_manager(spipe);
	return (1);
}
