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

int     exec_redir(char **env, t_command *cmd)
{
    int ret;
    t_command *tmp;
    pid_t   child;
    int     fd;
    t_parser comm1;

    comm1 = get_command(cmd->argument);
}
/*Executer la redirection avant chaque commande
Changer le fd dans le main programme ofc pour exec la commande de base dans le bon fd
dup stdin + out dans deux int pour pas les perdre et les reset a chaque commande
Utiliser les redirs commes crees dans le parser de Pierre aka comm->redir
*/

int     create_files_out(t_list *file)
{
    while (file)
    {
        if (file->content)
        {
            if (open(file->content, O_RDONLY) == -1)
                if (open(file->content, O_CREAT) == -1)
                    return (0);
            
        }
        else
        {
            return (0);
        }
        file = file->next;
    }
    return (1);
}

int    redir_manager(char **env, t_command *cmd)
{
    t_list  *tmp;

    tmp = cmd->redir_out;
    if (tmp && tmp->content)
        if (!create_files_out(tmp))
            return (0);
    tmp = cmd->redir_out;
    if (tmp && tmp->content)
    {
        if (!exec_redir(env, cmd))
            return (0);
    }
    return (1);
}

int     exec_redir_in(char **env, t_command *cmd, t_list *redir)
{
    int ret;
    pid_t   child;
    t_list *tmp;
    int     fd;
    t_parser comm1;

    comm1 = get_command(cmd->argument);
    tmp = redir;
    ret = 0;
    while (tmp)
    {
        if (tmp->content)
        {
            if ((child = fork()) == 0)
            {
                if ((fd = open(tmp->content, O_RDONLY)) == -1)
                    return (0);
                dup2(fd, 0);
                if (cmd->argument && cmd->argument->content)
                    execve(ft_path(env, comm1), comm1.argument,  env);
            }
            waitpid(child, &ret, 0);
        }
        else
        {
            return (0);
        }
        tmp = tmp->next;
    }
    return (1);
}

int     listlen(t_command *list)
{
    t_command *tmp;
    int i;

    tmp = list;
    i = 1;
    while (tmp->pipe)
    {
        i++;
        tmp = tmp->pipe;
    }
    return (i);
}

int     simple_command(char ** env, t_command *cmd)
{
    pid_t child;
    int ret;
    t_parser comm1;

    comm1 = get_command(cmd->argument);
    if (cmd->redir_in || cmd->redir_out || cmd->redir_append)
    {
        printf ("Coucou je suis la\n");
        redir_manager(env, cmd);
        return(0);
    }
    else if ((child = fork()) == 0)
    {
        execve(ft_path(env, comm1), comm1.argument, env);
    }
    waitpid(child, &ret, 0);
    return (0);
}

int     execution(char **env, t_command *cmd)
{
   	s_pipe spipe;
    int i;

    i = 0;
    spipe.i_comm = 0;
    spipe.i_pipe = 0;
    spipe.n_comm = listlen(cmd);
    spipe.n_pipe = spipe.n_comm - 1;
    if (spipe.n_comm == 1)
    {
        simple_command(env, cmd);
    }
    else if (spipe.n_comm == 2)
    {
        single_pipe(env, cmd);
    }
    else if (spipe.n_comm > 2)
    {
        multi_pipe(env, cmd, &spipe);
    }
    else
    {
        ft_putendl_fd("Il est con ce gosse", 0);
    }
    return (1);
}
