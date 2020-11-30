/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:39:22 by psemsari          #+#    #+#             */
/*   Updated: 2020/11/30 17:31:28 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

int     redir_manager(char **env, t_command *cmd);
int     exec_redir_in(char **env, t_command *cmd, t_list *redir);
int     listlen(t_command *list);
int     multi_pipe(char **env, t_command *cmd, int pip[2]);
int     simple_command(char ** env, t_command *cmd);
int     single_pipe(char **env, t_command *command);
int     exec_pipe(char **env, t_command *command, int pipe[2]);
int     create_files_out(t_list *file);
int     execution(char **env, t_command *cmd);

#endif
