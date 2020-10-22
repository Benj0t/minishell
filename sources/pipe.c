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
    int child2;
    int ret;
    t_parser comm1;
    t_parser comm2;

    comm1 = get_command(command1);
    comm2 = get_command(command2);
    if (pipe(p) < 0)
        return (-1);
    if ((child = fork()) == 0)
    {
        dup2(p[1], 1);
        close(p[0]);
        execve(ft_path(env, command1), comm1.argument, env);   
    }
    if ((child2 = fork()) == 0)
    {
        dup2(p[0], 0);
        close(p[1]);
        execve(ft_path(env, command2), comm2.argument,  env);
    }
    close(p[0]);
    close(p[1]);
    waitpid(child2, &ret, 0);
    waitpid(child, &ret, 0);
    return (1);
}

int     create_files_out(t_list *file)
{
    while (file)
    {
        if (file->content)
            if (open(file->content, O_RDONLY) == -1)
                if (open(file->content, O_CREAT) == -1)
                    return (0);
        else
        {
            return (0);
        }
        file = file->next;
    }
    return (1);
}


// WAITPID ???
// GARDER LE RETOUR DU EXECVE ???
// aled
// Fork en boucle tant que y a une redir et waitpid a la fin de la boucle en desincrementant // Du coup maybe need un tableau de child.
// C est c que je fais deja un peu je crois

int     exec_redir_in(char **env, t_command *cmd, t_list *redir)
{
    int child;
    int fd;

    while (redir)
    {
        if (redir->content)
        {
            if ((child = fork()) == 0)
            {
                if (fd = open(redir->content, O_RDONLY) == -1)
                    return (0);
                dup2(fd, 0);
                if (cmd->argument && cmd->argument.content)
                    execve(ft_path(env, cmd->argument.content),/* A CONVERTIR EN ARRAY */ cmd->argument, env);
            }
            //FAIRE UN AUTRE BAIL
        }
        else
        {
            return (0);
        }
        redir = redir->next;
    }
    return (1);
}

int     pipe_command(env)
{
    //REFLECIHR A UN AUTRE BAIL
}
// Faudrait il pas pipe avant d exec tout
// appeler les fonctions d exec dans les pipes, chaque fork eecutant un cote du pipe et ensuite le main process waitpid tout
// le pipe se fait il au debut de l exec ou au moment ou il pop dans les args ???

int    ft_exec(char **env, t_command *cmd)
{
    t_list  *tmp;

    tmp = &(cmd->redir_out);
    if (tmp && tmp->content)
        if (!create_files_out(tmp))
            return (0);
    tmp = &(cmd->redir_in);
    if (tmp && tmp->content)
        if (!exec_redir_in(env. cmd, tmp))
            return (0);
}