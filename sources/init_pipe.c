/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:24:08 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/18 14:49:08 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			init_pipe(s_pipe *spipe)
{
	int i;

	i = 0;
	while (i < spipe->n_pipe)
	{
		if (!(spipe->p[i] = (int *)malloc(sizeof(int) * (2))))
			return (0);
		if (pipe(spipe->p[i++]) < 0)
			return (0);
	}
	return (1);
}

int			init_spipe(s_pipe *spipe)
{
	int i;

	spipe->path = NULL;
	spipe->l_env = NULL;
	i = 0;
	if (!(spipe->p = (int **)malloc(sizeof(int *) * (spipe->n_pipe))))
		return (0);
	if (!init_pipe(spipe))
		return (0);
	if (!(spipe->child = (pid_t *)malloc(sizeof(pid_t) * (spipe->n_comm))))
		return (0);
	if (!(spipe->pid = (int *)malloc(sizeof(int) * (spipe->n_comm))))
		return (0);
	i = 0;
	while (i < spipe->n_comm)
		spipe->pid[i++] = -1;
	i = 0;
	if (!(spipe->ret = (int *)malloc(sizeof(int) * (spipe->n_comm))))
		return (0);
	i = 0;
	while (i < spipe->n_comm)
		spipe->ret[i++] = 0;
	return (1);
}

void		free_spipe(s_pipe *spipe)
{
	int i;

	i = 0;
	if (spipe->n_pipe)
		while (i < spipe->n_pipe)
			free(spipe->p[i++]);
	free(spipe->child);
	free(spipe->pid);
	free(spipe->ret);
	if (spipe->l_env)
	{
		dealloc_tab(spipe->l_env);
		spipe->l_env = NULL;
	}
	if (spipe->path)
		free(spipe->path);
}

char		*init_path(char **env, t_parser command, s_pipe *spipe)
{
	if (spipe->path)
		free(spipe->path);
	spipe->path = ft_path(env, command);
	if (!(spipe->path))
		exit(127);
	return (spipe->path);
}

char		**set_local_env(s_pipe *spipe)
{
	if (spipe->l_env)
	{
		dealloc_tab(spipe->l_env);
		spipe->l_env = NULL;
	}
	spipe->l_env = list_to_envp();
	return (spipe->l_env);
}
