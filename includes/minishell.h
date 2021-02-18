#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef struct	s_command
{
		t_list			*argument;
		t_list			*redir_append;
		t_list			*redir_out;
		t_list			*redir_in;
		struct s_command	*pipe;
}				t_command;

typedef struct	s_var_env
{
	char	*key;
	char	*var;
}				t_var_env;

typedef struct	s_parser
{
		char	*command;
		char	**argument;
}				t_parser;

extern t_list *g_env;

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
# include "pipe.h"
# include "parser.h"

int			listlen(t_command *list);
int			gnl_prompt(int fd, char **line, int *last_ret);
int			prompt_rec(int check, char *str, char **line, int *last_ret);
int			ft_pipe(char **env, char *command1, char *command2);
int			ft_cd(char **arg);
int			ft_pwd(void);
void		print_env(void);
t_list		*envp_to_list(char **envp);
void		set_env_var(char *key, char* var);
char		**list_to_envp(void);
int			valid_env(char *s);
int			check_env(char *s);
char		*get_env_var(char *search);
int			unset(char	**arg);
int			list_env(void);
void		modified_env(char *key, char* var);
int			ft_echo(char **arg);
int			ft_exit(char **arg);
void		clear_multi_command(t_command *command);

# include "path.h"
# include "pipe.h"

#endif
