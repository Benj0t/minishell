/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:53:51 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/18 05:43:24 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_quit(int sigid)
{
	if (sigid == SIGQUIT)
	{
		write(1, "\n", 1);
		exit(9);
	}
}

void		exec_fcomm_1(t_redir *redir, s_pipe *spipe, t_parser comm1)
{
	if (redir->std_out == -1)
		dup2(spipe->prev_p[1], 1);
	close(spipe->prev_p[0]);
	execve(init_path(spipe->l_env, comm1, spipe),\
			comm1.argument, spipe->l_env);
}

void		exec_fcomm_2(t_redir *redir, s_pipe *spipe, t_parser comm2)
{
	if (redir->std_in == -1)
		dup2(spipe->prev_p[0], 0);
	close(spipe->prev_p[1]);
	if (redir->std_out == -1)
		dup2(spipe->curr_p[1], 1);
	close(spipe->curr_p[0]);
	execve(init_path(spipe->l_env, comm2, spipe),\
			comm2.argument, spipe->l_env);
}

static int	second_command(t_list *env, t_command *cmd,\
			s_pipe *spipe, t_redir *redir)
{
	t_parser	comm2;

	comm2 = get_command(cmd->pipe->argument);
	set_local_env(env, spipe);
	if (exec_redir(cmd, redir) == -1)
		return (0);
	if ((spipe->ret[spipe->index] = scan_builtins(cmd->pipe, env, spipe)) == 1)
	{
		if (redir->std_in == -1)
			dup2(spipe->prev_p[0], 0);
			spipe->ret[1] = builtins(cmd->pipe, env, spipe);
	}
	if (spipe->ret[spipe->index++] == -1 &&\
		(spipe->child[spipe->i_comm++] = fork()) == 0)
		exec_fcomm_2(redir, spipe, comm2);
	end_redir(redir);
	if (redir->std_out != -1)
		return (0);
	close_pipe(spipe);
	return (1);
}

void		close_pipe(s_pipe *spipe)
{
	close(spipe->prev_p[0]);
	close(spipe->prev_p[1]);
	spipe->prev_p[0] = spipe->curr_p[0];
	spipe->prev_p[1] = spipe->curr_p[1];
}

int			first_command(t_list *env, t_command *cmd,\
			s_pipe *spipe, t_redir *redir)
{
	t_parser comm1;

	if (pipe(spipe->prev_p) < 0 || pipe(spipe->curr_p) < 0)
		return (0);
	if (exec_redir(cmd, redir) == -1)
		return (0);
	set_local_env(env, spipe);
	if ((spipe->ret[0] = scan_builtins(cmd, env, spipe)) == 1)
	{
		if (redir->std_in == -1 && redir->std_out == -1)
			dup2(spipe->prev_p[1], 1);
		builtins(cmd, env, spipe);
	}
	signal(SIGQUIT, &sig_quit);
	spipe->child[spipe->i_comm++] = fork();
	if (spipe->ret[spipe->index++] == -1 &&\
		(spipe->child[spipe->i_comm - 1] == 0))
		exec_fcomm_1(redir, spipe, comm1);
	end_redir(redir);
	if (redir->std_out != -1)
		return (0);
	return (second_command(env, cmd, spipe, redir));
}
