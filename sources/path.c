/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:08:51 by marvin            #+#    #+#             */
/*   Updated: 2021/03/01 00:47:41 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		error_msg(t_pipe *spipe, struct stat buf, int ret)
{
	spipe->b_ret[spipe->index] = 8;
	if (!(buf.st_mode & S_IFREG) && ret == 0)
		spipe->b_ret[spipe->index] = 6;
	if (!(buf.st_mode & S_IXUSR) && ret == 0)
		spipe->b_ret[spipe->index] = 7;
}

char		*rel_path(char **env, t_parser comm, t_pipe *spipe)
{
	struct stat	buf;
	int			ret;

	ret = 0;
	(void)env;
	if ((ret = stat(comm.argument[0], &buf)) == 0 && (buf.st_mode & S_IXUSR)\
												&& (buf.st_mode & S_IFREG))
		return (ft_strdup(comm.argument[0]));
	error_msg(spipe, buf, ret);
	return (NULL);
}

int			rel_char(char *name)
{
	int i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char		*try_exec(char **tab, char **name, t_parser comm, t_pipe *spipe)
{
	struct stat buf;
	int			i;

	i = -1;
	while (tab[++i])
	{
		if ((*name = ft_strjoin_c(tab[i], comm.command, '/')) == NULL)
		{
			dealloc_tab(tab);
			return (NULL);
		}
		if (stat(*name, &buf) == 0)
			if (buf.st_mode & S_IFREG)
				if (buf.st_mode & S_IXUSR)
				{
					spipe->b_ret[spipe->index] = 1;
					dealloc_tab(tab);
					return (*name);
				}
		spipe->b_ret[spipe->index] = 127;
		free(*name);
	}
	return (NULL);
}

char		*ft_path(char **env, t_parser comm, t_pipe *spipe)
{
	char		*s;
	char		**tab;
	int			i;

	if (rel_char(comm.command))
	{
		s = rel_path(env, comm, spipe);
		return (s);
	}
	i = get_path_id(env);
	if (i < 0 || (tab = ft_split(env[i] + 5, ':')) == NULL)
		return (NULL);
	i = 0;
	if (!rel_char(comm.command))
		if ((s = try_exec(tab, &s, comm, spipe)))
			return (s);
	dealloc_tab(tab);
	return (NULL);
}
