/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 04:32:57 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/26 00:09:22 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_child;

void		exec_middle_command(t_redir *redir, t_pipe *spipe, t_parser comm1, t_command *command)
{
	if (redir->std_in == -1)
		dup2(spipe->prev_p[0], 0);
	close(spipe->prev_p[1]);
	if (redir->std_out == -1)
		dup2(spipe->curr_p[1], 1);
	close(spipe->curr_p[0]);
	if (spipe->b_ret[spipe->index] == 0)
		exit(builtins(command, spipe));
	else if (spipe->b_ret[spipe->index] == 1)
		execve(spipe->path, comm1.argument, spipe->l_env);
}

int			middle_commands(t_command *cmd,\
			t_pipe *spipe, t_redir *redir)
{
	int			ret;
	t_parser	comm1;

	if (pipe(spipe->curr_p) < 0)
		return (0);
	if ((get_command(cmd->argument, &comm1)) == -1)
		free_struct(spipe, &comm1, cmd);
	set_local_env(spipe);
	if (exec_redir(cmd, redir) == -1)
		return (-1);
	spipe->b_ret[++spipe->index] = scan_builtins(cmd, spipe);
	if (init_path(spipe->l_env, comm1, spipe) == NULL && spipe->b_ret[spipe->index] == 1)
		return (spipe->ret[spipe->index] = invalid_command(spipe, &comm1));
	if ((g_child = fork()) == 0)
		exec_middle_command(redir, spipe, comm1, cmd);
	spipe->child[spipe->index] = g_child;
	end_redir(redir);
	++(spipe->i_pipe);
	close_pipe(spipe);
	free(comm1.argument);
	return (0);
}
