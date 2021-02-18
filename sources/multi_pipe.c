/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:19:00 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/18 14:49:57 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_middle_command(t_redir *redir, s_pipe *spipe, t_parser comm1)
{
	if (redir->std_in == -1)
		dup2(spipe->p[spipe->i_pipe][0], 0);
	close(spipe->p[spipe->i_pipe][1]);
	if (redir->std_out == -1)
		dup2(spipe->p[spipe->i_pipe + 1][1], 1);
	close(spipe->p[spipe->i_pipe + 1][0]);
	execve(init_path(spipe->l_env, comm1, spipe),\
			comm1.argument, spipe->l_env);
}

static int	middle_commands(t_command *cmd,\
			s_pipe *spipe, t_redir *redir)
{
	int			ret;
	t_parser	comm1;

	comm1 = get_command(cmd->argument);
	set_local_env(spipe);
	exec_redir(cmd, redir);
	spipe->ret[spipe->index] = builtins(cmd, spipe);
	if (spipe->ret[spipe->index++] == -1 &&\
		(spipe->child[spipe->i_comm++] = fork()) == 0)
		exec_middle_command(redir, spipe, comm1);
	close(spipe->p[spipe->i_pipe][0]);
	close(spipe->p[spipe->i_pipe][1]);
	if (redir->std_out != -1)
	{
		end_redir(redir);
		return (0);
	}
	end_redir(redir);
	++spipe->i_pipe;
	return (1);
}

static int	last_command(t_command *cmd,\
						s_pipe *spipe, t_redir *redir)
{
	int			ret;
	t_parser	comm1;

	comm1 = get_command(cmd->argument);
	set_local_env(spipe);
	exec_redir(cmd, redir);
	spipe->ret[spipe->index] = builtins(cmd, spipe);
	if (spipe->ret[spipe->index++] == -1 &&\
		(spipe->child[spipe->i_comm++] = fork()) == 0)
	{
		if (redir->std_in == -1)
			dup2(spipe->p[spipe->i_pipe][0], 0);
		close(spipe->p[spipe->i_pipe][1]);
		execve(init_path(spipe->l_env, comm1, spipe),\
			comm1.argument, spipe->l_env);
	}
	close(spipe->p[spipe->i_pipe][0]);
	close(spipe->p[spipe->i_pipe][1]);
	end_redir(redir);
	if (redir->std_out != -1)
		return (0);
	++spipe->i_pipe;
	return (1);
}

int			multi_pipe(t_command *cmd,\
						s_pipe *spipe, t_redir *redir)
{
	int			i;
	int			ret;
	t_command	*tmp;

	spipe->index = 0;
	i = 0;
	tmp = cmd;
	while (i < spipe->n_pipe - 1 && tmp)
	{
		if (i == 0)
		{
			ret = first_command(tmp, spipe, redir);
			tmp = tmp->pipe;
		}
		if (i > 0)
		{
			ret = middle_commands(tmp, spipe, redir);
		}
		tmp = tmp->pipe;
		i++;
	}
	ret = last_command(tmp, spipe, redir);
	spipe->i_pipe++;
	get_ret_values(spipe);
	return (1);
}
