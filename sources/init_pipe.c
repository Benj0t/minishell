/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:24:08 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/28 20:34:42 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_null(t_pipe *spipe)
{
	spipe->i_comm = 0;
	spipe->i_pipe = 0;
	spipe->n_pipe = spipe->n_comm - 1;
	spipe->index = 0;
	spipe->path = NULL;
	spipe->child = NULL;
	spipe->l_env = NULL;
	spipe->pid = NULL;
	spipe->ret = NULL;
}

int			init_spipe(t_pipe *spipe)
{
	int i;

	i = 0;
	set_null(spipe);
	if (!(spipe->child = (pid_t *)malloc(sizeof(pid_t) * (spipe->n_comm))))
		return (free_spipe(spipe));
	if (!(spipe->pid = (int *)malloc(sizeof(int) * (spipe->n_comm))))
		return (free_spipe(spipe));
	if (!(spipe->ret = (int *)malloc(sizeof(int) * (spipe->n_comm))))
		return (free_spipe(spipe));
	if (!(spipe->b_ret = (int *)malloc(sizeof(int) * (spipe->n_comm))))
		return (free_spipe(spipe));
	while (i < spipe->n_comm)
	{
		spipe->b_ret[i] = 0;
		spipe->child[i] = 0;
		spipe->ret[i] = 0;
		spipe->pid[i++] = 0;
	}
	return (1);
}

char		*init_path(char **env, t_parser command, t_pipe *spipe)
{
	if (spipe->path)
	{
		free(spipe->path);
		spipe->path = NULL;
	}
	if (command.argument && !ft_strncmp("", command.argument[0], 1))
		return (NULL);
	if (command.argument && !ft_strncmp(".", command.argument[0], 2))
	{
		spipe->b_ret[spipe->index] = 2;
		return (NULL);
	}
	spipe->path = ft_path(env, command, spipe);
	if (!(spipe->path))
		return (NULL);
	return (spipe->path);
}

char		**set_local_env(t_pipe *spipe)
{
	if (spipe->l_env)
	{
		dealloc_tab(spipe->l_env);
		spipe->l_env = NULL;
	}
	spipe->l_env = list_to_envp();
	return (spipe->l_env);
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
