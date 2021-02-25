/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:21:23 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/25 02:01:09 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		get_ret_values(t_pipe *spipe)
{
	int i;
	int end;

	i = 0;
	end = spipe->index - 1;
	while (end >= 0)
	{
		if (spipe->b_ret[end] == 1)
		{
			waitpid(spipe->child[end], (int *)&(spipe->pid[i]), 0);
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

int			invalid_command(t_pipe *spipe, t_parser comm1)
{
	if (spipe->b_ret[spipe->index] == 0)
	{
		free(comm1.argument);
		return (0);
	}
	if (spipe->b_ret[spipe->index] == 2)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		free(comm1.argument);
		return (2);
	}
	ft_putstr_fd(comm1.argument[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(comm1.argument);
	return (127);
}

void		close_pipe(t_pipe *spipe)
{
	close(spipe->prev_p[0]);
	close(spipe->prev_p[1]);
	spipe->prev_p[0] = spipe->curr_p[0];
	spipe->prev_p[1] = spipe->curr_p[1];
}
