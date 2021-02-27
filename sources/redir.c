/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:52:01 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/27 22:26:30 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		try_rdonly(int *fd, t_list *tmp, t_redir *redir, t_pipe *spipe)
{
	if ((*fd = open(((t_redirection *)tmp->content)->arg,\
								O_RDONLY, 0644)) == -1)
		return (err_msg("Can't open redirection file !", spipe));
	if (tmp->next == NULL)
	{
		dup2(*fd, 0);
		redir->std_in = *fd;
	}
	else
	{
		close(*fd);
	}
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
	if (tmp->next == NULL)
	{
		dup2(*fd, 1);
		redir->std_out = *fd;
	}
	else
	{
		close(*fd);
	}
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
	if (tmp->next == NULL)
	{
		dup2(*fd, 1);
		redir->std_out = *fd;
	}
	else
	{
		close(*fd);
	}
	return (0);
}

int		exec_redir(t_command *cmd, t_redir *redir, t_pipe *spipe)
{
	t_list	*tmp;
	int		fd;

	save_std(redir, cmd);
	if (cmd == NULL || cmd->redirection == NULL)
		return (1);
	tmp = cmd->redirection;
	while (tmp && tmp->content)
	{
		if (((t_redirection *)tmp->content)->in == 1)
			if (try_rdonly(&fd, tmp, redir, spipe) == -1)
				return (-1);
		if (((t_redirection *)tmp->content)->out == 1)
			if (try_wronly(&fd, tmp, redir, spipe) == -1)
				return (-1);
		if (((t_redirection *)tmp->content)->append == 1)
		{
			if (try_append(&fd, tmp, redir, spipe) == -1)
			{
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
