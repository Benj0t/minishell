/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:28:02 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/27 22:44:27 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/param.h>
# include "parser.h"

typedef struct				s_pipe
{
	char					**str;
	int						*b_ret;
	int						n_bin;
	char					*path;
	char					**l_env;
	int						last_ret;
	int						curr_p[2];
	int						prev_p[2];
	int						*ret;
	int						*pid;
	pid_t					*child;
	int						n_pipe;
	int						n_comm;
	int						i_comm;
	int						i_pipe;
	int						index;
}							t_pipe;

typedef struct				s_redir
{
	int						std_in;
	int						std_out;
	int						save_stdin;
	int						save_stdout;
}							t_redir;

typedef struct				s_cd
{
	char					*previous;
	char					*home;
	char					*pwd;
	char					*tmp;
	char					*new;
	int						ret;
	int						bool;
}							t_cd;

typedef	struct				s_redirection
{
	char					*arg;
	int						in;
	int						out;
	int						append;
}							t_redirection;

typedef	struct				s_command
{
	t_list					*argument;
	t_list					*redirection;
	struct s_command		*pipe;
}							t_command;

typedef struct				s_var_env
{
	char					*key;
	char					*var;
}							t_var_env;

typedef struct				s_parser
{
	char					*command;
	char					**argument;
}							t_parser;

typedef struct				s_managparse
{
	t_command				*command;
	t_redir					*redir;
	t_pipe					*spipe;
	int						is_in_quote;
	char					*str;
}							t_managparse;

typedef enum				e_ttoken
{
	tok_word,
	tok_space,
	tok_tab,
	tok_out,
	tok_in,
	tok_end,
	tok_pipe,
	tok_eof,
	tok_error,
	tok_null
}							t_ttoken;

typedef struct				s_token
{
	char					*name;
	t_ttoken				type;
}							t_token;

extern t_list				*g_env;

int							invalid_command(t_pipe *spipe, t_parser *comm1);
void						close_pipe(t_pipe *spipe);
void						end_redir(t_redir *redir);
char						**set_local_env(t_pipe *spipe);
int							free_spipe(t_pipe *spipe);
int							first_command(t_command *cmd,\
							t_pipe *spipe, t_redir *redir);
int							second_command(t_command *cmd,\
							t_pipe *spipe, t_redir *redir);
void						dealloc_tab(char **tab);
char						*init_path(char **env,\
							t_parser command, t_pipe *spipe);
char						**set_local_env(t_pipe *spipe);
int							builtins(t_command *cmd, t_pipe *spipe,\
													t_parser *parse);
int							ft_ret(int *ret);
void						end_redir(t_redir *redir);
int							exec_redir(t_command *cmd, t_redir *redir,\
															t_pipe *spipe);
int							redir_manager(char **env, t_command *cmd);
int							create_files_in(t_list *file);
int							exec_redir_in(char **env,\
							t_command *cmd, t_list *redir);
int							listlen(t_command *list);
int							multi_pipe(t_command *cmd,\
							t_pipe *spipe, t_redir *redir);
int							simple_command(t_command *cmd,\
							t_redir *redir, t_pipe *spipe);
int							left_pipe(t_command *command,\
							t_redir *redir, t_pipe *spipe);
int							right_pipe(t_command *command,\
							t_redir *redir, t_pipe *spipe);
int							single_pipe(t_command *command,\
							t_redir *redir, t_pipe *spipe);
int							exec_pipe(char **env,\
							t_command *command, int pipe[2]);
int							create_files_out(t_list *file);
int							exec_redir_out(char **env,\
							t_command *cmd, t_list *redir);
int							execution(t_command *cmd,\
							t_redir *redir, t_pipe *spipe);
void						get_ret_values(t_pipe *spipe);
void						pid_manager(t_pipe *spipe);
int							init_pipe(t_pipe *spipe);
int							init_spipe(t_pipe *spipe);
int							err_msg(char *str, t_pipe *spipe);
int							middle_commands(t_command *cmd,\
							t_pipe *spipe, t_redir *redir);
void						save_std(t_redir *redir, t_command *cmd);

char						in_list(char c, char *str);
t_ttoken					search_type(char c);
int							is_quote(char c);
int							backslash(char *str, size_t i);
int							is_backslash(char *str, size_t i);
t_token						word_tok(t_managparse *manag, size_t i);
t_token						others_tok(t_managparse *manag);
t_token						error_quote(t_managparse *manag, char quote);
size_t						quote_pass(t_managparse *manag,\
							size_t i, char quote);
t_token						next_token(t_managparse *manag);
void						dealloc_redirection(void *content);

char						*join_name(t_token *tok,\
							t_managparse *manag, char *result);
char						*dup_name(t_token *tok, t_managparse *manag,\
										char *result, size_t i);
char						*dbl_join(t_token *tok, t_managparse *manag,\
										char *var, size_t ret);
char						*var_to_replace(t_token *tok,\
							t_managparse *manag, char *tmp);
char						*ft_subvar(char *name, t_managparse *manag);
int							get_len(char *str);
char						*get_value(char *str, size_t *i);
char						*join_protect(char *str1, char *str2);
void						simple_quote(char **result, size_t *i, \
							t_token *tok, t_managparse *manag);
int							environnment_expander(char **result, size_t *i,\
							t_token *tok, t_managparse *manag);
int							double_quote(char **result, size_t *i,\
							t_token *tok, t_managparse *manag);
int							quote_exp(char **result, size_t *i,\
							t_token *tok, t_managparse *manag);
void						add_char(char **result, size_t *i,\
							t_token *tok, t_managparse *manag);
void						remove_backslash(char **result, size_t *i,\
							t_token *tok, t_managparse *manag);
void						remove_backslash_check(char **result, size_t *i,\
							t_token *tok, t_managparse *manag);
int							expansion(t_token *tok,\
							t_managparse *manag, size_t i);
int							backslash_lvl(char *str, size_t i);

t_redirection				*malloc_redirection(char *arg, int flag);
void						malloc_fail(t_token tok, t_managparse *manag);
int							error_parser(char *str, char *name);
int							save_arg(t_token *tok,\
							t_managparse *manag, int flag);
int							test_arg(t_token *tok,\
							t_managparse *manag, int flag);
void						next_free_token(t_token *tok, t_managparse *manag);
int							save_tok_out(t_token *tok, t_managparse *manag);
int							save_tok_append(t_token *tok, t_managparse *manag);
int							save_tok_in(t_token *tok, t_managparse *manag);
int							save_tok_pipe(t_token *tok, t_managparse *manag);
int							parser_token(t_managparse *manag);

void						clear_multi_command(t_command *command);
t_command					*setup_command(void);
int							parser(char **str, t_redir *redir, t_pipe *spipe);

int							get_command(t_list *argument, t_parser *parse);
int							get_path_id(char **env);
char						*ft_path(char **env,\
							t_parser comm, t_pipe *spipe);

int							cd_error(char *error);
int							add_dot(void);
int							free_struct(t_pipe *spipe,\
							t_parser *parser, t_command *command);
int							prompt_malloc(char **line, char *str);
void						bubble_sort(t_list *list);
void						ft_lstrm(t_list **lst);
t_list						*ft_lstcopy(t_list *head);

int							check_env(char *s);
int							valid_env(char *s);
void						print_env(char	*prefix, t_list *env);
void						print_export(char	*prefix, t_list *env);
t_var_env					*malloc_varenv(const char *key, const char *str);
void						dealloc_varenv(void *content);
t_list						*envp_to_list(char **envp);
char						**list_to_envp(void);
void						dealloc_tab(char **tab);
char						*get_env(const char *name);
t_var_env					*getvar_env(const char *name);
int							put_env(char *string);
int							set_env(const char *name, char *value, int replace);
int							contains_egal(const char *name);
int							unset_env(const char *name);

int							is_valid_env(char *s);
int							scan_builtins(t_command *cmd, t_pipe *spipe,\
													t_parser *parse);
int							listlen(t_command *list);
int							gnl_prompt(int fd, char **line, int *last_ret);
int							prompt_rec(int check, char *str,\
							char **line, int *last_ret);
int							ft_pipe(char **env, char *command1, char *command2);
int							ft_cd(char **arg);
int							ft_pwd(void);
int							ft_exit(char **arg, t_pipe *spipe,\
							t_command *command);
int							ft_env(void);
int							ft_echo(char **arg);
int							ft_unset(char **arg);
int							ft_export(char **arg);
void						clear_multi_command(t_command *command);

int							ft_isnum(char *str);
long long int				ft_atoll(const char *str);
unsigned long long int		ft_atoull(const char *str);
unsigned long long int		ft_getull(const char *str);
int							ft_strcmp(const char *s1, const char *s2);

#endif
