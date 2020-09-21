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

char    *path(char **env)
{
    char *path;
    int i;
    int found;
    int ret;
    pid_t child;

    i = 0;
    ret = 0;
    found = 0;
    path = ft_strjoin(env[i], "/ls");
    child = fork();
    env = NULL;
    if (child == 0)
    {
        printf("%d %s\n", execve(path, ft_split("ls", ' '), env), strerror(errno));
    }
    else
    {
        waitpid(child, &ret, 0);
        printf("%d", ret);
    }
    
    return (path);
}