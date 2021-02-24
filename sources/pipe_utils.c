/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:21:23 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/24 00:31:26 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		get_ret_values(s_pipe *spipe)
{
	int i;
	int end;

	i = 0;
	end = spipe->index;
	while (end > 0)
	{
		if (spipe->ret[end] == 1)
		{
			waitpid(spipe->child[spipe->n_bin--], (int *)&(spipe->pid[i]), 0);
			spipe->ret[end] = WEXITSTATUS(spipe->pid[i++]);
		}
		end--;
	}
}

int			listlen(t_command *list)
{
	int i;

	i = 1;
	if (!list)
		return (0);
	while (list->pipe != NULL)
	{
		i++;
		list = list->pipe;
	}
	return (i);
}

int			invalid_command(s_pipe *spipe, t_parser comm1)
{
	ft_putstr_fd(comm1.argument[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}

void		close_pipe(s_pipe *spipe)
{
	close(spipe->prev_p[0]);
	close(spipe->prev_p[1]);
	spipe->prev_p[0] = spipe->curr_p[0];
	spipe->prev_p[1] = spipe->curr_p[1];
}
