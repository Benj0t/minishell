/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:52:01 by bemoreau          #+#    #+#             */
/*   Updated: 2021/01/25 07:28:53 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		try_rdonly(int *fd, t_list *tmp, t_redir *redir)
{
	if ((*fd = open(tmp->content, O_RDONLY)) == -1)
		return (err_msg("Can't open redirection file !"));
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

int		try_wronly(int *fd, t_list *tmp, t_redir *redir)
{
	if ((*fd = open(tmp->content, O_WRONLY)) == -1)
	{
		if ((*fd = open(tmp->content, O_CREAT)) == -1)
			return (err_msg("Can't create redirection file !"));
		else
		{
			close(*fd);
			if ((*fd = open(tmp->content, O_WRONLY)) == -1)
				return (err_msg("Can't open redirection file !"));
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

int		try_append(int *fd, t_list *tmp, t_redir *redir)
{
	if ((*fd = open(tmp->content, O_WRONLY | O_APPEND)) == -1)
	{
		if ((*fd = open(tmp->content, O_CREAT)) == -1)
			return (err_msg("Can't create redirection file !"));
		else
		{
			close(*fd);
		}
		if ((*fd = open(tmp->content, O_WRONLY | O_APPEND)) == -1)
			return (err_msg("Can't append redirection file !"));
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

int		exec_redir(t_command *cmd, t_redir *redir)
{
	t_list	*tmp;
	int		fd;

	save_std(redir, &tmp, cmd);
	while (tmp && tmp->content)
	{
		if (try_rdonly(&fd, tmp, redir) == -1)
			return (-1);
		tmp = tmp->next;
	}
	tmp = cmd->redir_out;
	while (tmp && tmp->content)
	{
		if (try_wronly(&fd, tmp, redir) == -1)
			return (-1);
		tmp = tmp->next;
	}
	tmp = cmd->redir_append;
	while (tmp && tmp->content)
	{
		if (try_append(&fd, tmp, redir) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (1);
}
