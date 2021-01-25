/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:08:51 by marvin            #+#    #+#             */
/*   Updated: 2021/01/25 05:16:38 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	get_command(t_list *argument)
{
	t_parser	parse;
	int			len;
	int			i;

	len = ft_lstsize(argument);
	parse.argument = (char **)malloc(sizeof(char *) * (len + 1));
	parse.argument[len] = NULL;
	i = -1;
	while (++i < len)
	{
		parse.argument[i] = argument->content;
		argument = argument->next;
	}
	parse.command = parse.argument[0];
	return (parse);
}

int			get_path_id(char **env)
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

char		*rel_path(char **env, t_parser comm, struct stat buf)
{
	int ret;
	int child;

	child = fork();
	if (child == 0)
	{
		if (!stat(comm.argument[0], &buf))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(child, &ret, 0);
		if (ret != -1 && ret != 256)
			return (ft_strdup(comm.argument[0]));
	}
	return (NULL);
}

int			stat_loop(char *path, struct stat *buf, int *ret)
{
	pid_t		child;

	child = fork();
	if (child == 0)
	{
		if (!stat(path, buf))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(child, ret, 0);
		if (*ret != -1 && *ret != 256)
			return (1);
		else
		{
			free(path);
		}
	}
	return (0);
}

char		*ft_path(char **env, t_parser comm)
{
	char		*path;
	char		**tab;
	int			ret;
	int			i;
	struct stat	buf;

	path = rel_path(env, comm, buf);
	if (path)
		return (path);
	if ((i = get_path_id(env)) < 0)
		return (NULL);
	tab = ft_split(env[i] + 5, ':');
	i = 0;
	ret = 0;
	path = NULL;
	path = ft_strjoin_c(tab[i], comm.command, '/');
	while (tab[i] && !(stat_loop(path, &buf, &ret)))
		path = ft_strjoin_c(tab[++i], comm.command, '/');
	dealloc_tab(tab);
	return (path);
}
