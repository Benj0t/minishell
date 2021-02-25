/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:53:51 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/25 01:21:59 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_fcomm_2(t_redir *redir, t_pipe *spipe, t_parser comm2)
{
	if (redir->std_in == -1)
		dup2(spipe->prev_p[0], 0);
	close(spipe->prev_p[1]);
	if (redir->std_out == -1)
		dup2(spipe->curr_p[1], 1);
	close(spipe->curr_p[0]);
	execve(spipe->path, comm2.argument, spipe->l_env);
}

static int	second_command(t_command *cmd,\
			t_pipe *spipe, t_redir *redir)
{
	t_parser	comm2;

	if (exec_redir(cmd->pipe, redir) == -1)
		return (0);
	if ((get_command(cmd->pipe->argument, &comm2)) == -1)
		free_struct(spipe, &comm2, cmd);
	set_local_env(spipe);
	if ((spipe->b_ret[spipe->index] = scan_builtins(cmd->pipe, spipe)) == 0)
	{
		if (redir->std_in == -1)
			dup2(spipe->prev_p[0], 0);
		if (redir->std_out == -1)
			dup2(spipe->curr_p[1], 1);
		spipe->ret[spipe->index] = builtins(cmd->pipe, spipe);
	}
	if (init_path(spipe->l_env, comm2, spipe) == NULL)
		invalid_command(spipe, comm2);
	if (spipe->b_ret[spipe->index++] == 1 &&\
		(spipe->child[spipe->i_comm++] = fork()) == 0)
		exec_fcomm_2(redir, spipe, comm2);
	end_redir(redir);
	if (redir->std_out != -1)
		return (0);
	close_pipe(spipe);
	free(comm2.argument);
	return (1);
}

void		exec_fcomm_1(t_redir *redir, t_pipe *spipe, t_parser comm1)
{
	if (redir->std_out == -1)
		dup2(spipe->prev_p[1], 1);
	close(spipe->prev_p[0]);
	execve(spipe->path, comm1.argument, spipe->l_env);
}

int			first_command(t_command *cmd,\
			t_pipe *spipe, t_redir *redir)
{
	t_parser comm1;

	if (exec_redir(cmd, redir) == -1)
		return (0);
	if (pipe(spipe->curr_p) < 0 || pipe(spipe->prev_p) < 0)
		return (0);
	set_local_env(spipe);
	if ((get_command(cmd->argument, &comm1)) == -1)
		free_struct(spipe, &comm1, cmd);
	if ((spipe->b_ret[spipe->index] = scan_builtins(cmd, spipe)) == 0)
	{
		if (redir->std_out == -1)
			dup2(spipe->prev_p[1], 1);
		spipe->ret[spipe->index] = builtins(cmd, spipe);
	}
	if (init_path(spipe->l_env, comm1, spipe) == NULL)
		spipe->ret[spipe->index] = invalid_command(spipe, comm1);
	if (spipe->b_ret[spipe->index++] == 1 &&\
		((spipe->child[spipe->i_comm++] = fork()) == 0))
		exec_fcomm_1(redir, spipe, comm1);
	end_redir(redir);
	if (redir->std_out != -1)
		return (0);
	free(comm1.argument);
	return (second_command(cmd, spipe, redir));
}
