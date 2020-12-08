/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:52:01 by bemoreau          #+#    #+#             */
/*   Updated: 2020/12/08 15:52:01 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		end_redir(t_redir *redir)
{
    if (redir->std_in != -1)
    {
        dup2(redir->save_stdin, 0);
        close(redir->save_stdin);
        close(redir->std_in);
    }
    if (redir->std_out != -1)
    {
        dup2(redir->save_stdout, 1);
        close(redir->save_stdout);
        close(redir->std_out);
    }
}

int     exec_redir(t_command *cmd, t_redir *redir)
{
    int ret;
    t_list *tmp;
    int     fd;

    tmp = cmd->redir_in;
    redir->save_stdin = dup(0);
    redir->save_stdout = dup(1);
	redir->std_in = -1;
	redir->std_out = -1;
    while (tmp && tmp->content)
    {
        if ((fd = open(tmp->content, O_RDONLY)) == -1)
        {
            ft_putendl_fd("Can't open redirection file !", 1);
            return (-1);
        }
        if (tmp->next == NULL)
        {
            dup2(fd, 0);
            redir->std_in = fd;
        }
        else
        {
            close(fd);
        }
        tmp = tmp->next;
    }
    tmp = cmd->redir_out;
    while (tmp && tmp->content)
    {
        if ((fd = open(tmp->content, O_WRONLY)) == -1)
        {
            if ((fd = open(tmp->content, O_CREAT)) == -1)
            {
                ft_putendl_fd("Can't create redirection file !", 1);
                return (-1);
            }
            else
            {
                close(fd);
                if ((fd = open(tmp->content, O_WRONLY)) == -1)
                {
                    ft_putendl_fd("Can't open redirection file !", 1);
                    return (-1);
                }
            }
        }
        if (tmp->next == NULL)
        {
			printf("LE FD WESH\n");
            dup2(fd, 1);
			redir->std_out = fd;
        }
        else
        {
            close(fd);
        }
        tmp = tmp->next;
    }
    return (1);
}