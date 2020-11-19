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

#include "../includes/minishell.h"

// t_parser get_command(char const *str)
// {
// 	t_parser	parse;

// 	parse.argument = ft_split(str, ' ');
// 	parse.command = parse.argument[0];
// 	return (parse);
// }

int     get_path_id(char **env)
{
    int i;

//     i = 0;
//     while (env[i])
//     {
//         if (!ft_strncmp("PATH=", env[i], 5))
//             return (i);
//         i++;
//     }
//     return (-1);
// }
 
char        *ft_path(char **env, char *str)
{
    char *path;
    char **tab;
    int id;
    int found;
    int ret;
    int i;
    pid_t child;
    struct stat buf;
    t_parser command;

//     if ((id = get_path_id(env)) < 0)
//         return (NULL);
//     i = 0;
//     ret = 0;
//     found = 0;
//     tab = ft_split(env[id] + 5, ':');
//     path = NULL;
//     command = get_command(str);
//     while (!found)
//     {
//         path = ft_strjoin_c(tab[i], command.command, '/');
//         child = fork();
//         if (child == 0)
//         {

            if (!stat(path, &buf))
                exit(EXIT_SUCCESS);
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(child, &ret, 0);
            if (ret != -1 && ret != 256)
                found = 1;
            else
            {
                free(path);
            }
        }
        i++;
    }
    return (path);
}
