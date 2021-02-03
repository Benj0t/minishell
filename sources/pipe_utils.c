/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 04:21:23 by bemoreau          #+#    #+#             */
/*   Updated: 2021/01/27 13:57:30 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		get_ret_values(s_pipe *spipe)
{
	int i;

	i = 0;
	while (spipe->i_pipe >= 0)
	{
		if (spipe->ret[i] == 0)
		{
			waitpid(spipe->child[spipe->i_pipe--], (int *)&(spipe->pid[i]), 0);
			spipe->ret[i] = WEXITSTATUS(spipe->pid[i]);
		}
		i++;
	}
}
