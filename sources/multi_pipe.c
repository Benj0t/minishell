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

static int		first_command(t_list *env, t_command *cmd, s_pipe *spipe, t_redir *redir)
{
	
    t_parser comm1;
    t_parser comm2;

    exec_redir(cmd, redir);
    comm1 = get_command(cmd->argument);
    comm2 = get_command(cmd->pipe->argument);
    spipe->ret[spipe->index] = builtins(cmd, env, spipe);
    if (spipe->ret[spipe->index++] == -1 && (spipe->child[spipe->i_comm++] = fork()) == 0)
    {
        if (redir->std_out == -1)
            dup2(spipe->p[spipe->i_pipe][1], 1);
        close(spipe->p[spipe->i_pipe][0]);
        execve(ft_path(list_to_envp(env), comm1), comm1.argument, list_to_envp(env));
    }
    if (redir->std_out != -1)
    {
        end_redir(redir);
        return (0);
    }
    end_redir(redir);
    exec_redir(cmd->pipe, redir);
    spipe->ret[spipe->index] = builtins(cmd, env, spipe);
    if (spipe->ret[spipe->index++] == -1 && (spipe->child[spipe->i_comm++] = fork()) == 0)
    {
        if (redir->std_in == -1)
            dup2(spipe->p[spipe->i_pipe][0], 0);
		close(spipe->p[spipe->i_pipe][1]);
		if (redir->std_out == -1)
            dup2(spipe->p[spipe->i_pipe + 1][1], 1);
        close(spipe->p[spipe->i_pipe + 1][0]);
        execve(ft_path(list_to_envp(env), comm2), comm2.argument,  list_to_envp(env));
    }
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

static int		middle_commands(t_list *env, t_command *cmd, s_pipe *spipe, t_redir *redir)
{
	int ret;
	t_parser comm1;

	comm1 = get_command(cmd->argument);
    exec_redir(cmd, redir);
    spipe->ret[spipe->index] = builtins(cmd, env, spipe);
    if (spipe->ret[spipe->index++] == -1 && (spipe->child[spipe->i_comm++] = fork()) == 0)
    {
        if (redir->std_in == -1)
            dup2(spipe->p[spipe->i_pipe][0], 0);
		close(spipe->p[spipe->i_pipe][1]);
		if (redir->std_out == -1)
            dup2(spipe->p[spipe->i_pipe + 1][1], 1);
        close(spipe->p[spipe->i_pipe + 1][0]);
        execve(ft_path(list_to_envp(env), comm1), comm1.argument, list_to_envp(env));
    }
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

static int		last_command(t_list *env, t_command *cmd, s_pipe *spipe, t_redir *redir)
{
	int ret;
	t_parser comm1;

	comm1 = get_command(cmd->argument);
    exec_redir(cmd, redir);
    spipe->ret[spipe->index] = builtins(cmd, env, spipe);
    if (spipe->ret[spipe->index++] == -1 && (spipe->child[spipe->i_comm++] = fork()) == 0)
    {
        if (redir->std_in == -1)
            dup2(spipe->p[spipe->i_pipe][0], 0);
		close(spipe->p[spipe->i_pipe][1]);
        execve(ft_path(list_to_envp(env), comm1), comm1.argument,  list_to_envp(env));
    }
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

int     		multi_pipe(t_list *env, t_command *cmd, s_pipe *spipe, t_redir *redir)
{
    int			i;
    int         fd;
    int         ret;
	t_command	*tmp;

    spipe->index = 0;
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
	if (!(spipe->pid = (int *)malloc(sizeof(int) * (spipe->n_comm + 1))))
        return (0);
    i = 0;
    while ( i <= spipe->n_comm)
        spipe->pid[i++] = -1;
    i = 0;
	if (!(spipe->ret = (int *)malloc(sizeof(int) * (spipe->n_comm + 1))))
        return (0);
    i = 0;
    while ( i <= spipe->n_comm)
        spipe->ret[i++] = -1;
    i = 0;
    spipe->pid[spipe->n_comm] = -1;
    while (i < spipe->n_pipe - 1 && tmp)
    {
        if (i == 0)
        {
            ret = first_command(env, tmp, spipe, redir);
            tmp = tmp->pipe;
        }
        if (i > 0 && ret == 1)
            ret = middle_commands(env, tmp, spipe, redir);
        tmp = tmp->pipe;
        i++;
    }
    if (ret == 1)
    {
        ret = last_command(env, tmp, spipe, redir);
    }
    spipe->i_pipe++;
    i = 0;
    while (spipe->i_pipe >= 0)
    {
        if (spipe->ret[i] == -1)
        {
            waitpid(spipe->child[spipe->i_pipe--], (int *)&(spipe->pid[i]), 0);
            spipe->ret[i] = WEXITSTATUS(spipe->pid[i]);
        }
        i++;
    }
	return (1);
}

int    single_pipe(t_list *env, t_command *command, t_redir *redir, s_pipe *spipe)
{
    int p[2];
    int child;
    int child2;
    t_parser comm1;
    t_parser comm2;

    if (!(spipe->pid = (int *)malloc(sizeof(int) * (3))))
        return (-1);
    spipe->pid[0] = -1;
    spipe->pid[1] = -1;
    spipe->pid[2] = -1;
    if (!(spipe->ret = (int *)malloc(sizeof(int) * (3))))
        return (-1);
    spipe->ret[2] = -1;
    comm1 = get_command(command->argument);
    comm2 = get_command(command->pipe->argument);
    exec_redir(command, redir);
    if (pipe(p) < 0)
        return (-1);
    spipe->ret[0] = builtins(command, env, spipe);
    if (spipe->ret[0] == -1 && (child = fork()) == 0)
    {
        if (redir->std_in == -1 && redir->std_out == -1)
            dup2(p[1], 1);
        close(p[0]);
        execve(ft_path(list_to_envp(env), comm1), comm1.argument, list_to_envp(env));
        if (redir->std_out != -1)
        {
            end_redir(redir);
            return (0);
        }
    }
    end_redir(redir);
    exec_redir(command->pipe, redir);
    spipe->ret[1] = builtins(command, env, spipe);
    if (spipe->ret[1] == -1 && (child2 = fork()) == 0)
    {
        if (redir->std_in == -1)
            dup2(p[0], 0);
        close(p[1]);
        execve(ft_path(list_to_envp(env), comm2), comm2.argument,  list_to_envp(env));
    }
    end_redir(redir);
    close(p[0]);
    close(p[1]);
    if (spipe->ret[0] == -1)
    {
        waitpid(child, (int *)&(spipe->pid[0]), 0);
        spipe->ret[0] = WEXITSTATUS(spipe->pid[0]);
    }
    if (spipe->ret[1] == -1)
    {
        waitpid(child, (int *)&(spipe->pid[1]), 0);
        spipe->ret[1] = WEXITSTATUS(spipe->pid[1]);
    }
    return (1);
}
