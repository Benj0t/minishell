/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:21:23 by bemoreau          #+#    #+#             */
/*   Updated: 2021/03/01 00:43:44 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_child;
extern int	g_signal_b;
extern int	g_signal_c;

void		get_ret_values(t_pipe *spipe)
{
	int i;

	i = spipe->index;
	while (i >= 0)
	{
		if (spipe->b_ret[i] == 1)
		{
			waitpid(spipe->child[i], (int *)&(spipe->pid[i]), 0);
			spipe->ret[i] = WEXITSTATUS(spipe->pid[i]);
			if (g_signal_b == 131)
			{
				spipe->ret[i] = 131;
				g_signal_b = 0;
			}
			if (g_signal_c == 1)
			{
				spipe->ret[i] = 130;
				g_signal_c = 0;
			}
		}
		i--;
	}
}

void		pid_manager(t_pipe *spipe)
{
	int i;

	i = 1;
	while (i > -1)
	{
		if (spipe->b_ret[i] == 1)
		{
			waitpid(spipe->child[i], (int *)&(spipe->pid[i]), 0);
			spipe->ret[i] = WEXITSTATUS(spipe->pid[i]);
		}
		if (g_signal_b == 131)
		{
			spipe->ret[i] = 131;
			g_signal_b = 0;
		}
		if (g_signal_c == 1)
		{
			spipe->ret[i] = 130;
			g_signal_b = 0;
		}
		i--;
	}
}

int			listlen(t_command *list)
{
	int i;

	i = 1;
	if (!list || !list->argument || !list->argument->content)
		return (0);
	while (list->pipe != NULL)
	{
		i++;
		list = list->pipe;
	}
	return (i);
}

int			invalid_command(t_pipe *spipe, t_parser *comm1)
{
	if (spipe->b_ret[spipe->index] == 3)
		ft_putstr_fd("minishell: permission denied\n", 2);
	if (spipe->b_ret[spipe->index] == 2)
		ft_putstr_fd("minishell: .: command not found\n", 2);
	if (spipe->b_ret[spipe->index] == 6)
		ft_putstr_fd("minishell: file is a directory\n", 2);
	if (spipe->b_ret[spipe->index] == 7)
		ft_putstr_fd("minishell: Can not execute your file\n", 2);
	if (spipe->b_ret[spipe->index] == 8)
		ft_putstr_fd("minishell: Can not find or execute your file\n", 2);
	if (spipe->b_ret[spipe->index] == 3 || spipe->b_ret[spipe->index] == 6 ||\
								spipe->b_ret[spipe->index] == 7)
	{
		free(comm1->argument);
		return (126);
	}
	if (spipe->b_ret[spipe->index] == 2 || spipe->b_ret[spipe->index] == 8)
	{
		free(comm1->argument);
		return (127);
	}
	ft_putstr_fd(comm1->argument[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(comm1->argument);
	return (127);
}

void		close_pipe(t_pipe *spipe)
{
	close(spipe->prev_p[0]);
	close(spipe->prev_p[1]);
	spipe->prev_p[0] = spipe->curr_p[0];
	spipe->prev_p[1] = spipe->curr_p[1];
}
