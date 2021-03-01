/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 05:39:44 by bemoreau          #+#    #+#             */
/*   Updated: 2021/03/01 00:43:58 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_redir(t_redir *redir)
{
	dup2(redir->save_stdin, 0);
	if (redir->save_stdin != -1)
		close(redir->save_stdin);
	if (redir->std_in != -1)
		close(redir->std_in);
	dup2(redir->save_stdout, 1);
	if (redir->save_stdout != -1)
		close(redir->save_stdout);
	if (redir->std_out != -1)
		close(redir->std_out);
	redir->std_out = -1;
	redir->std_in = -1;
}

int		err_msg(char *str, t_pipe *spipe)
{
	ft_putendl_fd(str, 2);
	spipe->ret[spipe->index] = 1;
	return (-1);
}

void	save_std(t_redir *redir, t_command *cmd)
{
	(void)cmd;
	redir->save_stdin = dup(0);
	redir->save_stdout = dup(1);
	redir->std_in = -1;
	redir->std_out = -1;
}
