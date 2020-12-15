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

    if (!(spipe->ret = (int *)malloc(sizeof(int) * (2))))
        return (1);
    spipe->ret[1] = -1;
    comm1 = get_command(cmd->argument);
    exec_redir(cmd, redir);
    if ((child = fork()) == 0)
        execve(ft_path(env, comm1), comm1.argument, env);
    end_redir(redir);
    waitpid(child, (int *)&(spipe->ret[0]), 0);
    return (0);
}

int     ft_print_ret(int *ret)
{
    int i;

    i = 0;
    while (ret[i] != -1)
    {
        i++;
    }
    ft_putnbr_fd((unsigned char)ret[i - 1], 1);
    ft_putchar_fd('\n', 1);
    return (0);
}

int     execution(char **env, t_command *cmd, t_redir *redir, s_pipe *spipe)
{
    int i;

    i = 0;
    spipe->n_comm = listlen(cmd);
    spipe->i_comm = 0;
    spipe->i_pipe = 0;
    spipe->n_pipe = spipe->n_comm - 1;
    if ((ft_memcmp(cmd->argument->content, "$?", 2)) == 12)
    {
        ft_print_ret(spipe->ret);
    }
    if (spipe->n_comm == 1)
    {
        simple_command(env, cmd, redir, spipe);
    }
    else if (spipe->n_comm == 2)
    {
        single_pipe(env, cmd, redir, spipe);
    }
    else if (spipe->n_comm > 2)
    {
        multi_pipe(env, cmd, spipe, redir);
    }
    else
    {
        ft_putendl_fd("Il est con ce gosse", 1);
    }
    return (1);
}
