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

int     listlen(t_command *list)
{
	int i;

	i = 1;
	if (!list)
		return (0);
	while (list->pipe != NULL)
	{
		i++;
		list = list->pipe;
	}
	return (i);
}

int     simple_command(char ** env, t_command *cmd, t_redir *redir, s_pipe *spipe)
{
    pid_t child;
    t_parser comm1;

    if (!(spipe->pid = (int *)malloc(sizeof(int) * (2))))
        return (1);
    spipe->pid[0] = -1;
    spipe->pid[1] = -1;
    if (!(spipe->ret = (int *)malloc(sizeof(int) * (2))))
        return (1);
    spipe->ret[0] = -1;
    spipe->ret[1] = -1;
    comm1 = get_command(cmd->argument);
    exec_redir(cmd, redir);
    if ((child = fork()) == 0)
        execve(ft_path(env, comm1), comm1.argument, env);
    end_redir(redir);
    waitpid(child, (int *)&(spipe->pid[0]), 0);
    spipe->ret[0] = WEXITSTATUS(spipe->pid[0]);
    return (0);
}

int     ft_ret(int *ret)
{
    int i;

    i = 0;
    while (ret[i] != -1)
    {
        i++;
    }
    return((unsigned char)ret[i - 1]);
}

int     execution(t_list *env, t_command *cmd, t_redir *redir, s_pipe *spipe)
{
    t_parser test;
    int i;

    i = 0;
    test = get_command(cmd->argument);
    if (ft_strncmp(test.command, "cd", 3) == 0)
        return (ft_cd(test.argument, env));
    if (ft_strncmp(test.command, "unset", 6) == 0)
        return (unset(test.argument, env));
    if (ft_strncmp(test.command, "env", 4) == 0)
        return (list_env(env));
    if (ft_strncmp(test.command, "echo", 5) == 0)
        return (ft_echo(test.argument));
    if (ft_strncmp(test.command, "exit", 5) == 0)
        return (ft_exit(test.argument));
    spipe->n_comm = listlen(cmd);
    spipe->i_comm = 0;
    spipe->i_pipe = 0;
    spipe->n_pipe = spipe->n_comm - 1;
    if (spipe->n_comm == 1)
    {
        simple_command(list_to_envp(env), cmd, redir, spipe);
    }
    else if (spipe->n_comm == 2)
    {
        single_pipe(list_to_envp(env), cmd, redir, spipe);
    }
    else if (spipe->n_comm > 2)
    {
        multi_pipe(list_to_envp(env), cmd, spipe, redir);
    }
    else
    {
        ft_putendl_fd("Il est con ce gosse", 1);
    }
    return (1);
}
