/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:39:22 by psemsari          #+#    #+#             */
/*   Updated: 2020/12/02 18:56:52 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

typedef struct	t_pipe
{
	int			**p;
	int			*ret;
	pid_t		*child;
	int			n_pipe;
	int			n_comm;
	int			i_comm;
	int			i_pipe;
}				s_pipe;


int     redir_manager(char **env, t_command *cmd);
int     exec_redir_in(char **env, t_command *cmd, t_list *redir);
int     listlen(t_command *list);
int     multi_pipe(char **env, t_command *cmd, s_pipe *spipe);
int     simple_command(char ** env, t_command *cmd);
int     single_pipe(char **env, t_command *command);
int     exec_pipe(char **env, t_command *command, int pipe[2]);
int     create_files_out(t_list *file);
int     execution(char **env, t_command *cmd);

#endif
