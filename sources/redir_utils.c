/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 05:39:44 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/17 23:53:16 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_redir(t_redir *redir)
{
	dup2(redir->save_stdin, 0);
	close(redir->save_stdin);
	close(redir->std_in);

	dup2(redir->save_stdout, 1);
	close(redir->save_stdout);
	close(redir->std_out);
}

int		err_msg(char *str)
{
	ft_putendl_fd(str, 1);
	return (-1);
}

void	save_std(t_redir *redir, t_list **tmp, t_command *cmd)
{
	*tmp = cmd->redir_in;
	redir->save_stdin = dup(0);
	redir->save_stdout = dup(1);
	redir->std_in = -1;
	redir->std_out = -1;
}
