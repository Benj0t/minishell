/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:19:00 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/25 13:54:32 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_child;

void		exec_lcomm(t_pipe *spipe, t_redir *redir, t_parser comm1, t_command *command)
{
	if (redir->std_in == -1)
		dup2(spipe->prev_p[0], 0);
	close(spipe->prev_p[1]);
	if (spipe->b_ret[spipe->index] == 0)
		exit(builtins(command, spipe));
	else if (spipe->b_ret[spipe->index] == 1)
		execve(spipe->path, comm1.argument, spipe->l_env);
}

static int	last_command(t_command *cmd,\
						t_pipe *spipe, t_redir *redir)
{
	int			ret;
	t_parser	comm1;

	if (pipe(spipe->curr_p) < 0)
		return (1);
	if (exec_redir(cmd, redir) == -1)
		return (2);
	if ((get_command(cmd->argument, &comm1)) == -1)
		return (free_struct(spipe, &comm1, cmd));
	set_local_env(spipe);
	spipe->b_ret[++spipe->index] = scan_builtins(cmd, spipe);
	if (init_path(spipe->l_env, comm1, spipe) == NULL && spipe->b_ret[spipe->index] == 1)
		return (spipe->ret[spipe->index] = invalid_command(spipe, comm1));
	if ((g_child = fork()) == 0)
		exec_lcomm(spipe, redir, comm1, cmd);
	spipe->child[spipe->index] = g_child;
	++spipe->i_pipe;
	close_pipe(spipe);
	close(spipe->prev_p[0]);
	close(spipe->prev_p[1]);
	free(comm1.argument);
	return (0);
}

int			multi_pipe(t_command *cmd,\
						t_pipe *spipe, t_redir *redir)
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
			ret = second_command(tmp, spipe, redir);
			tmp = tmp->pipe;
		}
		if (i > 0)
			ret = middle_commands(tmp, spipe, redir);
		tmp = tmp->pipe;
		i++;
	}
	ret = last_command(tmp, spipe, redir);
	spipe->i_pipe++;
	get_ret_values(spipe);
	end_redir(redir);
	return (0);
}
