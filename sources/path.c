/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:08:51 by marvin            #+#    #+#             */
/*   Updated: 2021/02/25 15:58:52 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char		*rel_path(char **env, t_parser comm, struct stat buf, t_pipe *spipe)
{

	if (!(comm.argument[0][0] == '.' && comm.argument[0][1] == '/'))
		return (NULL);
	if (stat(comm.argument[0], &buf) == 0 && buf.st_mode & S_IXUSR)
	{
		return (ft_strdup(comm.argument[0]));
	}
	else
	{
		spipe->b_ret[spipe->index] = 3;
	}
	return (NULL);
}

char		*abs_path(char **env, t_parser comm, struct stat buf)
{
	if (!(comm.argument[0][0] == '/'))
		return (NULL);
	if (!stat(comm.argument[0], &buf))
		return (ft_strdup(comm.argument[0]));
	return (NULL);
}

char		*ft_path(char **env, t_parser comm, t_pipe *spipe)
{
	char		*path;
	char		**tab;
	int			ret;
	int			i;
	struct stat	buf;

	path = NULL;
	path = rel_path(env, comm, buf, spipe);
	if (spipe->b_ret[spipe->index] == 3)
		return (NULL);
	if (path)
		return (path);
	path = abs_path(env, comm, buf);
	if (path)
		return (path);
	if ((i = get_path_id(env)) < 0 || (tab = ft_split(env[i] + 5, ':')) == NULL)
		return (NULL);
	i = 0;
	ret = 0;
	if ((path = ft_strjoin_c(tab[i], comm.command, '/')) == NULL)
	{
		dealloc_tab(tab);
		return (NULL);
	}
	while (tab[i] && (stat(path, &buf) == -1))
	{
		free(path);
		path = ft_strjoin_c(tab[++i], comm.command, '/');
	}
	dealloc_tab(tab);
	return (path);
}
