#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>

typedef struct s_cd
{
	char		*previous;
	char		*home;
	char		*pwd;
	char		*tmp;
	char		*new;
	int			ret;
	int			bool;
}				t_cd;

typedef	struct	s_redirection
{
	char		*arg;
	int			in;
	int			out;
	int			append;
}					t_redirection;

typedef	struct	s_command
{
		t_list				*argument;
		t_list				*redirection;
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

void		free_struct(s_pipe *spipe, t_redir *redir, t_command *command);
int			prompt_malloc(char **line, char *str);
void		bubble_sort(t_list *list);
t_list*		ft_lstcopy(t_list* head);

int			check_env(char *s);
int			valid_env(char *s);
void		print_env(char	*prefix, t_list *env);
void		print_export(char	*prefix, t_list *env);
t_var_env	*malloc_varenv(const char *key, const char *str);
void		dealloc_varenv(void *content);
t_list		*envp_to_list(char **envp);
char		**list_to_envp(void);
void		dealloc_tab(char **tab);
char		*get_env(const char *name);
t_var_env	*getvar_env(const char *name);
int			put_env(char *string);
int			set_env(const char *name, char *value, int replace);
int			contains_egal(const char *name);
int			unset_env(const char *name);

int			is_valid_env(char *s);
int			scan_builtins(t_command *cmd, s_pipe *spipe);
int			listlen(t_command *list);
int			gnl_prompt(int fd, char **line, int *last_ret);
int			prompt_rec(int check, char *str, char **line, int *last_ret);
int			ft_pipe(char **env, char *command1, char *command2);
int			ft_cd(char **arg);
int			ft_pwd(void);
int			ft_exit(char **arg, s_pipe *spipe, t_command *command);
int			ft_env(void);
int			ft_echo(char **arg);
int			ft_unset(char **arg);
int			ft_export(char **arg);
void		clear_multi_command(t_command *command);

# include "path.h"
# include "pipe.h"

#endif
