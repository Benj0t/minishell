/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:19:00 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/20 06:11:46 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_lcomm(s_pipe *spipe, t_redir *redir, t_parser comm1)
{
	if (init_path(spipe->l_env, comm1, spipe) == NULL)
		invalid_command(spipe, comm1);
	if (redir->std_in == -1)
		dup2(spipe->prev_p[0], 0);
	close(spipe->prev_p[1]);
	execve(spipe->path, comm1.argument, spipe->l_env);
}

static int	last_command(t_list *env, t_command *cmd,\
						s_pipe *spipe, t_redir *redir)
{
	int			ret;
	t_parser	comm1;

	if (pipe(spipe->curr_p) < 0)
		return (1);
	comm1 = get_command(cmd->argument);
	set_local_env(env, spipe);
	if (exec_redir(cmd, redir) == -1)
		return (2);
	if ((spipe->ret[spipe->index] = scan_builtins(cmd, env, spipe)) == 1)
	{
		if (redir->std_in == -1)
			dup2(spipe->prev_p[0], 0);
		close(spipe->prev_p[1]);
		builtins(cmd, env, spipe);
	}
	if (spipe->ret[spipe->index++] == -1 &&\
		(spipe->child[spipe->i_comm++] = fork()) == 0)
		exec_lcomm(spipe, redir, comm1);
	end_redir(redir);
	if (redir->std_out != -1)
		return (0);
	++spipe->i_pipe;
	close_pipe(spipe);
	return (0);
}

int			multi_pipe(t_list *env, t_command *cmd,\
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
			ret = first_command(env, tmp, spipe, redir);
			tmp = tmp->pipe;
		}
		if (i > 0)
		{
			ret = middle_commands(env, tmp, spipe, redir);
		}
		tmp = tmp->pipe;
		i++;
	}
	ret = last_command(env, tmp, spipe, redir);
	spipe->i_pipe++;
	get_ret_values(spipe);
	return (0);
}
