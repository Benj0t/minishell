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

static int		first_command(char **env, t_command *cmd, s_pipe *spipe, int fd)
{
	
    int ret;
    t_parser comm1;
    t_parser comm2;

    comm1 = get_command(cmd->argument);
    comm2 = get_command(cmd->pipe->argument);
    if ((spipe->child[spipe->i_comm++] = fork()) == 0)
    {
        dup2(spipe->p[spipe->i_pipe][1], 1);
        close(spipe->p[spipe->i_pipe][0]);
        execve(ft_path(env, comm1), comm1.argument, env);
    }
    if ((spipe->child[spipe->i_comm++] = fork()) == 0)
    {
        dup2(spipe->p[spipe->i_pipe][0], 0);
		close(spipe->p[spipe->i_pipe][1]);
		dup2(spipe->p[spipe->i_pipe + 1][1], 1);
        close(spipe->p[spipe->i_pipe + 1][0]);
        execve(ft_path(env, comm2), comm2.argument,  env);
    }
    close(spipe->p[spipe->i_pipe][0]);
    close(spipe->p[spipe->i_pipe][1]);
	++spipe->i_pipe;
    return (1);
}

static int		middle_commands(char **env, t_command *cmd, s_pipe *spipe, int fd)
{
	int ret;
	t_parser comm1;

	comm1 = get_command(cmd->argument);
    if ((spipe->child[spipe->i_comm++] = fork()) == 0)
    {
        dup2(spipe->p[spipe->i_pipe][0], 0);
		close(spipe->p[spipe->i_pipe][1]);
		dup2(spipe->p[spipe->i_pipe + 1][1], 1);
        close(spipe->p[spipe->i_pipe + 1][0]);
        execve(ft_path(env, comm1), comm1.argument,  env);
    }
	// Maybe dup2 next pipe in main process
	close(spipe->p[spipe->i_pipe][0]);
    close(spipe->p[spipe->i_pipe][1]);
	++spipe->i_pipe;
	return (1);
}

static int		last_command(char **env, t_command *cmd, s_pipe *spipe, int fd)
{
	int ret;
	t_parser comm1;

	comm1 = get_command(cmd->argument);
    if ((spipe->child[spipe->i_comm++] = fork()) == 0)
    {
        dup2(spipe->p[spipe->i_pipe][0], 0);
		close(spipe->p[spipe->i_pipe][1]);
        execve(ft_path(env, comm1), comm1.argument,  env);
    }
	close(spipe->p[spipe->i_pipe][0]);
    close(spipe->p[spipe->i_pipe][1]);
	++spipe->i_pipe;
	return (1);
}

int     		multi_pipe(char **env, t_command *cmd, s_pipe *spipe)
{
    int			i;
    int         fd;
	t_command	*tmp;

    i = 0;
    fd = 1;
	tmp = cmd;
	if (!(spipe->p = (int **)malloc(sizeof(int *) * (spipe->n_pipe))))
		return (0);
	while (i < spipe->n_pipe)
	{
		if (!(spipe->p[i] = (int *)malloc(sizeof(int) * (2))))
			return (0);
		if (pipe(spipe->p[i++]) < 0)
        	return (0);
	}
	if (!(spipe->child = (pid_t *)malloc(sizeof(pid_t) * (spipe->n_comm + 1))))
        return (0);
    spipe->child[spipe->n_comm] = 0;
	
	if (!(spipe->ret = (int *)malloc(sizeof(int) * (spipe->n_comm + 1))))
        return (0);
    i = 0;
    t_parser comm1;
    while (i < spipe->n_pipe - 1 && tmp)
    {
        spipe->ret[i] = 0;
        if (i == 0)
        {
            first_command(env, tmp, spipe, fd);
            tmp = tmp->pipe;
        }
        if (i > 0)
            middle_commands(env, tmp, spipe, fd);
        tmp = tmp->pipe;
        i++;
    }
    last_command(env, tmp, spipe, fd);
    i = spipe->n_pipe;
    while (i > 0)
    {
        waitpid(spipe->child[i], &(spipe->ret[i]), 0);
        i--;
    }
	return (1);
}

int    single_pipe(char **env, t_command *command)
{
    int p[2];
    int child;
    int child2;
    int ret;
    t_parser comm1;
    t_parser comm2;

    comm1 = get_command(command->argument);
    comm2 = get_command(command->pipe->argument);
    if (pipe(p) < 0)
        return (-1);
    if ((child = fork()) == 0)
    {
        dup2(p[1], 1);
        close(p[0]);
        redir_manager(env, command);
        execve(ft_path(env, comm1), comm1.argument, env);
    }
    if (command->pipe->redir_append || command->pipe->redir_out || command->pipe->redir_in)
    {
        redir_manager(env, command->pipe);
        return (0);
    }
    else if ((child2 = fork()) == 0)
    {
        dup2(p[0], 0);
        close(p[1]);
        execve(ft_path(env, comm2), comm2.argument,  env);
    }
    close(p[0]);
    close(p[1]);
    waitpid(child2, &ret, 0);
    waitpid(child, &ret, 0);
    return (1);
}