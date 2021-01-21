/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:39:22 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/21 10:02:42 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "minishell.h"
# include "parser.h"

typedef struct	t_pipe
{
	int			last_ret;
	int			**p;
	int			*ret;
	int			*pid;
	pid_t		*child;
	int			n_pipe;
	int			n_comm;
	int			i_comm;
	int			i_pipe;
	int			index;
}				s_pipe;

typedef struct	s_redir
{
    int			std_in;
   	int 		std_out;
	int			save_stdin;
   	int 		save_stdout;
}				t_redir;

int		builtins(t_command *cmd, t_list *env, s_pipe *spipe);
int		parser(char *str, t_list *env, t_redir *redir, s_pipe *spipe);
int     ft_ret(int *ret);
void	end_redir(t_redir *redir);
int     exec_redir(t_command *cmd, t_redir *redir);
int     redir_manager(char **env, t_command *cmd);
int     create_files_in(t_list *file);
int     exec_redir_in(char **env, t_command *cmd, t_list *redir);
int     listlen(t_command *list);
int     multi_pipe(t_list *env, t_command *cmd, s_pipe *spipe, t_redir *redir);
int     simple_command(t_list *env, t_command *cmd, t_redir *redir, s_pipe *spipe);
int     single_pipe(t_list *env, t_command *command, t_redir *redir, s_pipe *spipe);
int     exec_pipe(char **env, t_command *command, int pipe[2]);
int     create_files_out(t_list *file);
int		exec_redir_out(char **env, t_command *cmd, t_list *redir);
int     execution(t_list *env, t_command *cmd, t_redir *redir, s_pipe *spipe);

#endif
