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

int    ft_pipe(char **env, char *command1, char *command2)
{
    int p[2];
    int child;
    t_parser comm1;
    t_parser comm2;

    comm1 = get_command(command1);
    comm2 = get_command(command2);
    if (pipe(p) < 0)
        return (-1);
    if ((child = fork()) == 0)
    {
        if ((child = fork()) == 0)
        {
            dup2(1, p[0]);
            execve(ft_path(env, command2), comm2.argument, env);   
        }
        else
        {
            dup2(0, p[1]);
            execve(ft_path(env, command1), comm1.argument,  env);
        }
    }
    return (1);
}