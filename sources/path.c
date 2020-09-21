/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:08:51 by marvin            #+#    #+#             */
/*   Updated: 2020/09/21 14:08:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  get_path_id(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (!ft_strncmp("PATH=", env[i], 5))
            return (i);
        i++;
    }
    return (-1);
}

char        *path(char **env)
{
    char *path;
    char **tab;
    int id;
    int found;
    int ret;
    int i;
    pid_t child;

    if ((id = get_path_id(env)) < 0)
        return (NULL);
    i = 0;
    ret = 0;
    found = 0;
    tab = ft_split(env[id] + 5, ':');
    path = NULL;
    while (!found)
    {
        path = ft_strjoin(tab[i], "/ls");
        child = fork();
        if (child == 0)
        {
            
            execve(path, ft_split("ls", ' '), env);
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(child, &ret, 0);
            if (ret != -1 && ret != 256)
            {
                printf("%s\n", tab[i]);
                found = 1;
            }
            else
            {
                free(path);
            }
        }
        i++;
    }
    return (path);
}