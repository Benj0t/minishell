/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 16:30:54 by marvin            #+#    #+#             */
/*   Updated: 2020/09/23 16:30:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		first_command(char **env, t_command *cmd, s_pipe spipe)
{
	
    int ret;
    t_parser comm1;
    t_parser comm2;

    comm1 = get_command(cmd->argument);
    comm2 = get_command(cmd->pipe->argument);
    if ((spipe.child[spipe.i_comm++] = fork()) == 0)
    {
        dup2(spipe.p[spipe.i_pipe][1], 1);
        close(spipe.p[spipe.i_pipe][0]);
        redir_manager(env, cmd);
        execve(ft_path(env, comm1), comm1.argument, env);
    }
    if ((spipe.child[spipe.i_comm++] = fork()) == 0)
    {
        dup2(spipe.p[spipe.i_pipe][0], 0);
		close(spipe.p[spipe.i_pipe][1]);
		dup2(spipe.p[spipe.i_pipe + 1][1], 1);
        close(spipe.p[spipe.i_pipe + 1][0]);
        execve(ft_path(env, comm2), comm2.argument,  env);
    }
    close(spipe.p[spipe.i_pipe][0]);
    close(spipe.p[spipe.i_pipe][1]);
	++spipe.i_pipe;
	cmd = cmd->pipe;
    return (1);
}

static int		middle_commands(char **env, t_command *cmd, s_pipe spipe)
{
	int ret;
	t_parser comm1;

	comm1 = get_command(cmd->argument);
    if ((spipe.child[spipe.i_comm++] = fork()) == 0)
    {
        dup2(spipe.p[spipe.i_pipe][0], 0);
		close(spipe.p[spipe.i_pipe][1]);
		dup2(spipe.p[spipe.i_pipe + 1][1], 1);
        close(spipe.p[spipe.i_pipe + 1][0]);
        execve(ft_path(env, comm1), comm1.argument,  env);
    }
	// Maybe dup2 next pipe in main process
	close(spipe.p[spipe.i_pipe][0]);
    close(spipe.p[spipe.i_pipe][1]);
	cmd = cmd->pipe;
	++spipe.i_pipe;
	return (1);
}

static int		last_command(char **env, t_command *cmd, s_pipe spipe)
{
	int ret;
	t_parser comm1;

	comm1 = get_command(cmd->argument);
    if ((spipe.child[spipe.i_comm++] = fork()) == 0)
    {
        dup2(spipe.p[spipe.i_pipe][0], 0);
		close(spipe.p[spipe.i_pipe][1]);
        execve(ft_path(env, comm1), comm1.argument,  env);
    }
	close(spipe.p[spipe.i_pipe][0]);
    close(spipe.p[spipe.i_pipe][1]);
	cmd = cmd->pipe;
	++spipe.i_pipe;
	return (1);
}

int     		multi_pipe(char **env, t_command *cmd, s_pipe spipe)
{
    int			i;
	t_command	*tmp;

    i = 0;
	tmp = cmd;
	if (!(spipe.p = (int **)malloc(sizeof(int *) * (spipe.n_pipe))))
		return (0);
	while (i < spipe.n_pipe)
	{
		if (!(spipe.p[i] = (int *)malloc(sizeof(int) * (2))))
			return (0);
		if (pipe(spipe.p[i++]) < 0)
        	return (0);
	}
	if (!(spipe.child = (pid_t *)malloc(sizeof(pid_t) * (spipe.n_comm + 1))))
        return (0);
    spipe.child[spipe.n_comm] = 0;
	
	return (1);
}