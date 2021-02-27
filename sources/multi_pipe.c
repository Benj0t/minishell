/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:19:00 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/27 12:38:33 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_child;

void		exec_lcomm(t_pipe *spipe, t_redir *redir, t_parser comm1,\
											t_command *command)
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

	if (exec_redir(cmd, redir) == -1)
		return (-1);
	if (pipe(spipe->curr_p) < 0)
		return (1);
	if ((get_command(cmd->argument, &comm1)) == -1)
		return (free_struct(spipe, &comm1, cmd));
	set_local_env(spipe);
	spipe->b_ret[++spipe->index] = scan_builtins(cmd, spipe);
	if (init_path(spipe->l_env, comm1, spipe) == NULL &&\
						spipe->b_ret[spipe->index] == 1)
		return (spipe->ret[spipe->index] = invalid_command(spipe, &comm1));
	if ((g_child = fork()) == 0)
		exec_lcomm(spipe, redir, comm1, cmd);
	spipe->child[spipe->index] = g_child;
	++spipe->i_pipe;
	close_pipe(spipe);
	close(spipe->prev_p[0]);
	close(spipe->prev_p[1]);
	free(spipe->path);
	free(comm1.argument);
	return (0);
}

int			multi_loop(t_command *tmp,\
						t_pipe *spipe, t_redir *redir, int i)
{
	int exec;
	int ret;

	while (i <= spipe->n_pipe && tmp)
	{
		exec = 0;
		if ((tmp->argument == NULL || tmp->argument->content == NULL))
		{
			exec = 1;
			exec_redir(tmp, redir);
		}
		if (i == 0 && exec == 0)
			ret = first_command(tmp, spipe, redir);
		if (i == 1 && exec == 0)
			ret = second_command(tmp, spipe, redir);
		if (i > 1 && i != spipe->n_pipe && exec == 0)
			ret = middle_commands(tmp, spipe, redir);
		if (i == spipe->n_pipe && exec == 0)
			ret = last_command(tmp, spipe, redir);
		tmp = tmp->pipe;
		end_redir(redir);
		i++;
	}
	return (ret);
}

int			multi_pipe(t_command *cmd,\
						t_pipe *spipe, t_redir *redir)
{
	int			i;
	int			ret;
	int			exec;
	t_command	*tmp;

	spipe->index = 0;
	i = 0;
	tmp = cmd;
	spipe->curr_p[0] = -1;
	spipe->curr_p[1] = -1;
	spipe->prev_p[0] = -1;
	spipe->prev_p[1] = -1;
	multi_loop(tmp, spipe, redir, 0);
	spipe->i_pipe++;
	get_ret_values(spipe);
	return (0);
}
