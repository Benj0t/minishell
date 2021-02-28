/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:52:01 by bemoreau          #+#    #+#             */
/*   Updated: 2021/03/01 00:10:43 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		try_rdonly(int *fd, t_list *tmp, t_redir *redir, t_pipe *spipe)
{
	if ((*fd = open(((t_redirection *)tmp->content)->arg,\
								O_RDONLY, 0644)) == -1)
		return (err_msg("Can't open redirection file !", spipe));
	if (redir->std_in != -1)
		close(redir->std_in);
	redir->std_in = *fd;
	return (0);
}

int		try_wronly(int *fd, t_list *tmp, t_redir *redir, t_pipe *spipe)
{
	if ((*fd = open(((t_redirection *)tmp->content)->arg,\
								O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		if ((*fd = open(((t_redirection *)tmp->content)->arg,\
									O_CREAT, 0644)) == -1)
			return (err_msg("Can't create redirection file !", spipe));
		else
		{
			close(*fd);
			if ((*fd = open(((t_redirection *)tmp->content)->arg,\
										O_WRONLY | O_TRUNC, 0644)) == -1)
				return (err_msg("Can't open redirection file !", spipe));
		}
	}
	if (redir->std_out != -1)
		close(redir->std_out);
	redir->std_out = *fd;
	return (0);
}

int		try_append(int *fd, t_list *tmp, t_redir *redir, t_pipe *spipe)
{
	if ((*fd = open(((t_redirection *)tmp->content)->arg,\
						O_WRONLY | O_APPEND, 0644)) == -1)
	{
		if ((*fd = open(((t_redirection *)tmp->content)->arg,\
											O_CREAT, 0644)) == -1)
			return (err_msg("Can't create redirection file !", spipe));
		else
		{
			close(*fd);
		}
		if ((*fd = open(((t_redirection *)tmp->content)->arg,\
								O_WRONLY | O_APPEND, 0644)) == -1)
			return (err_msg("Can't append redirection file !", spipe));
	}
	if (redir->std_out != -1)
		close(redir->std_out);
	redir->std_out = *fd;
	return (0);
}

void	dup_files(t_redir *redir)
{
	if (redir->std_in != -1)
		dup2(redir->std_in, 0);
	if (redir->std_out != -1)
		dup2(redir->std_out, 1);
}

int		exec_redir(t_command *cmd, t_redir *redir, t_pipe *spipe)
{
	t_list	*tmp;
	int		in;
	int		out;

	save_std(redir, cmd);
	if (cmd == NULL || cmd->redirection == NULL)
		return (1);
	tmp = cmd->redirection;
	in = 0;
	out = 0;
	while (tmp && tmp->content)
	{
		if (((t_redirection *)tmp->content)->in == 1)
			if (try_rdonly(&in, tmp, redir, spipe) == -1)
				return (-1);
		if (((t_redirection *)tmp->content)->out == 1)
			if (try_wronly(&out, tmp, redir, spipe) == -1)
				return (-1);
		if (((t_redirection *)tmp->content)->append == 1)
			if (try_append(&out, tmp, redir, spipe) == -1)
				return (-1);
		tmp = tmp->next;
	}
	dup_files(redir);
	return (1);
}
