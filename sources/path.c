/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:08:51 by marvin            #+#    #+#             */
/*   Updated: 2021/02/27 17:23:32 by bemoreau         ###   ########.fr       */
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
	int ret;

	ret = 0;
	if ((!(comm.argument[0][0] == '.' && comm.argument[0][1] == '/')))
		return (NULL);
	if ((ret = stat(comm.argument[0], &buf)) == 0 && (buf.st_mode & S_IXUSR)\
												&& S_ISREG(buf.st_mode) == 1)
		return (ft_strdup(comm.argument[0]));
	else
	{
		if (ret == 1)
			spipe->ret[spipe->index] = 127;
		else if ((S_ISREG(buf.st_mode) == 0))
		{
			spipe->b_ret[spipe->index] = 6;
		}
		else
			spipe->b_ret[spipe->index] = 7;
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

char		*try_path(char **env, t_parser comm, struct stat buf, t_pipe *spipe)
{
	char *path;

	path = NULL;
	if (spipe->b_ret[spipe->index] == 3)
		return (NULL);
	path = rel_path(env, comm, buf, spipe);
	if (path || spipe->b_ret[spipe->index] > 1)
		return (path);
	path = abs_path(env, comm, buf);
	return (path);
}

char		*ft_path(char **env, t_parser comm, t_pipe *spipe)
{
	char		*s;
	char		**tab;
	int			ret;
	int			i;
	struct stat	buf;

	if (s = try_path(env, comm, buf, spipe) || spipe->b_ret[spipe->index] > 1)
		return (s);
	i = get_path_id(env);
	if (i < 0 || (tab = ft_split(env[i] + 5, ':')) == NULL)
		return (NULL);
	i = 0;
	ret = 0;
	if ((s = ft_strjoin_c(tab[i], comm.command, '/')) == NULL)
	{
		dealloc_tab(tab);
		return (NULL);
	}
	while (tab[i] && (stat(s, &buf) == -1))
	{
		free(s);
		s = ft_strjoin_c(tab[++i], comm.command, '/');
	}
	dealloc_tab(tab);
	return (s);
}
