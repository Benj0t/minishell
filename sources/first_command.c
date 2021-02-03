/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:53:51 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/01 19:01:22 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t child;

static void	sig_quit(int sigid)
{
	if (sigid == SIGQUIT && child != 0)
	{
		write(1, "\n", 1);
		kill(child, SIGTERM);
	}
}

void		exec_fcomm_1(t_redir *redir, s_pipe *spipe, t_parser comm1)
{
	if (redir->std_out == -1)
		dup2(spipe->p[spipe->i_pipe][1], 1);
	close(spipe->p[spipe->i_pipe][0]);
	execve(init_path(spipe->l_env, comm1, spipe),\
			comm1.argument, spipe->l_env);
}

void		exec_fcomm_2(t_redir *redir, s_pipe *spipe, t_parser comm2)
{
	if (redir->std_in == -1)
		dup2(spipe->p[spipe->i_pipe][0], 0);
	close(spipe->p[spipe->i_pipe][1]);
	if (redir->std_out == -1)
		dup2(spipe->p[spipe->i_pipe + 1][1], 1);
	close(spipe->p[spipe->i_pipe + 1][0]);
	execve(init_path(spipe->l_env, comm2, spipe),\
			comm2.argument, spipe->l_env);
}

static int	second_command(t_list *env, t_command *cmd,\
			s_pipe *spipe, t_redir *redir)
{
	t_parser	comm2;

	comm2 = get_command(cmd->pipe->argument);
	set_local_env(env, spipe);
	exec_redir(cmd->pipe, redir);
	spipe->ret[spipe->index] = builtins(cmd, env, spipe);
	if (spipe->ret[spipe->index++] == -1 &&\
		(spipe->child[spipe->i_comm++] = fork()) == 0)
		exec_fcomm_2(redir, spipe, comm2);
	close(spipe->p[spipe->i_pipe][0]);
	close(spipe->p[spipe->i_pipe++][1]);
	end_redir(redir);
	if (redir->std_out != -1)
		return (0);
	return (1);
}

int			first_command(t_list *env, t_command *cmd,\
			s_pipe *spipe, t_redir *redir)
{
	t_parser comm1;

	exec_redir(cmd, redir);
	comm1 = get_command(cmd->argument);
	set_local_env(env, spipe);
	spipe->ret[spipe->index] = builtins(cmd, env, spipe);
	signal(SIGQUIT, &sig_quit);
	spipe->child[spipe->i_comm++] = fork();
	if (spipe->child[spipe->i_comm - 1])
		child = spipe->child[spipe->i_comm - 1];
	if (spipe->ret[spipe->index++] == -1 &&\
		(spipe->child[spipe->i_comm++] == 0))
		exec_fcomm_1(redir, spipe, comm1);
	end_redir(redir);
	if (redir->std_out != -1)
		return (0);
	return (second_command(env, cmd, spipe, redir));
}
