/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:39:22 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/23 20:23:44 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "minishell.h"

// /!\ CHANGER EN T_PIPE ENCULE

typedef struct	t_pipe
{
	int			n_bin;
	char		*path;
	char		**l_env;
	int			last_ret;
	int			curr_p[2];
	int			prev_p[2];
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

int		invalid_command(s_pipe *spipe, t_parser comm1);
void	close_pipe(s_pipe *spipe);
void	end_redir(t_redir *redir);
char	**set_local_env(s_pipe *spipe);
int		free_spipe(s_pipe *spipe);
int		first_command(t_command *cmd,\
		s_pipe *spipe, t_redir *redir);
void	dealloc_tab(char **tab);
char	*init_path(char **env, t_parser command, s_pipe *spipe);
char	**set_local_env(s_pipe *spipe);
int		builtins(t_command *cmd, s_pipe *spipe);
int		ft_ret(int *ret);
void	end_redir(t_redir *redir);
int		exec_redir(t_command *cmd, t_redir *redir);
int		redir_manager(char **env, t_command *cmd);
int		create_files_in(t_list *file);
int		exec_redir_in(char **env, t_command *cmd, t_list *redir);
int		listlen(t_command *list);
int		multi_pipe(t_command *cmd, s_pipe *spipe, t_redir *redir);
int		simple_command(t_command *cmd, t_redir *redir, s_pipe *spipe);
int		single_pipe(t_command *command, t_redir *redir, s_pipe *spipe);
int		exec_pipe(char **env, t_command *command, int pipe[2]);
int		create_files_out(t_list *file);
int		exec_redir_out(char **env, t_command *cmd, t_list *redir);
int		execution(t_command *cmd, t_redir *redir, s_pipe *spipe);
void	get_ret_values(s_pipe *spipe);
int		init_pipe(s_pipe *spipe);
int		init_spipe(s_pipe *spipe);
int		err_msg(char *str);
int		middle_commands(t_command *cmd, s_pipe *spipe, t_redir *redir);
void	save_std(t_redir *redir, t_list **tmp, t_command *cmd);
#endif
