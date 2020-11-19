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
        execve(ft_path(env, comm1.command), (char *)(command->argument->content), env);
    }
    if ((child2 = fork()) == 0)
    {
        dup2(p[0], 0);
        close(p[1]);
        execve(ft_path(env, comm2.command), (char *)(command->pipe->argument->content),  env);
    }
    close(p[0]);
    close(p[1]);
    waitpid(child2, &ret, 0);
    waitpid(child, &ret, 0);
    return (1);
}

int    exec_pipe(char **env, t_command *command, int pipes[2])
{
    int p[2];
    int child;
    int child2;
    int ret;
    t_parser comm1;
    t_parser comm2;

    dup2(pipes[0], 0);
    close(pipes[1]);
    comm1 = get_command(command->argument);
    comm2 = get_command(command->pipe->argument);
    if (pipe(p) < 0)
        return (-1);
    if ((child = fork()) == 0)
    {
        dup2(p[1], 1);
        close(p[0]);
        redir_manager(env, command);
        execve(ft_path(env, comm1.command), (char *)(command->argument->content), env);
        // FAIRE UN BAIL AVEC EXIT
    }
    if ((child2 = fork()) == 0)
    {
        dup2(p[0], 0);
        close(p[1]);
        execve(ft_path(env, comm2.command), (char *)(command->pipe->argument->content),  env);
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

int    redir_manager(char **env, t_command *cmd)
{
    t_list  *tmp;

    tmp = cmd->redir_out;
    if (tmp && tmp->content)
        if (!create_files_out(tmp))
            return (0);
    tmp = cmd->redir_in;
    if (tmp && tmp->content)
        if (!exec_redir_in(env, cmd, tmp))
            return (0);
    return (1);
}

int     exec_redir_in(char **env, t_command *cmd, t_list *redir)
{
    pid_t   child;
    t_list *tmp;
    int     fd;

    tmp = redir;
    while (tmp)
    {
        if (tmp->content)
        {
            if (fd = open(tmp->content, O_RDONLY) == -1)
                return (0);
            dup2(fd, 0);
            if (cmd->argument && cmd->argument->content)
                execve(ft_path(env, cmd->argument->content), (char *)(cmd->pipe->argument->content),  env);
        }
        //FAIRE UN AUTRE BAIL aka WaitPID
        // Ouais tu as raison mon reuf
        else
        {
            return (0);
        }
        tmp = tmp->next;
    }
    return (1);
}

// Faudrait il pas pipe avant d exec tout
// appeler les fonctions d exec dans les pipes, chaque fork executant un cote du pipe et ensuite le main process waitpid tout
// le pipe se fait il au debut de l exec ou au moment ou il pop dans les args ?

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

int     multi_pipe(char **env, t_command *cmd, int pip[2])
{
    int p[2];

    dup2(pip[0], 0);

    if (pipe(p) < 0)
        return (-1);

    multi_pipe(env, cmd->pipe, p);
}

int     simple_command(char ** env, t_command *cmd)
{
    pid_t child;
    int ret;
    t_parser comm1;

    comm1 = get_command(cmd->argument);
    if ((child = fork()) == 0)
    {
        execve(ft_path(env, comm1.command), (char *)(cmd->argument->content), env);
    }
    waitpid(child, &ret, 0);
    return (0);
}

int     execution(char **env, t_command *cmd)
{
   	pid_t *child;
    int l_len;
    int i;
    int pip[2];

    if (pipe(pip) == 0)
        return (NULL);
    i = 0;
    l_len = listlen(cmd);
    if (!(child = (pid_t *)malloc(sizeof(pid_t) * (l_len + 1))))
        return (0);
    child[l_len] = NULL;
    if (l_len == 0)
        simple_command(env, cmd);
    if (l_len == 1)
        single_pipe(env, cmd);
    else if (l_len > 1)
        multi_pipe(env, cmd, pip);
    else
    {
        redir_manager(env, cmd);
        execve(ft_path(env, cmd->argument->content), (char *)(cmd->pipe->argument->content), env);
    }
}
