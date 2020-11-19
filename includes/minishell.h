#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
# include "libft.h"
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "parser.h"
# include <sys/stat.h>

// typedef struct			s_parser
// {
// 	char				*command;
// 	char				**argument;
// }						t_parser;

// typedef struct	s_command
// {
// 		t_list				*argument;
// 		t_list				*redir_append;
// 		t_list				*redir_out;
// 		t_list				*redir_in;
// 		struct s_command	*pipe;
// }				t_command;
/*
typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
*/
int			ft_pipe(char **env, char *command1, char *command2);
int			ft_cd(char **env, char *dir);
int			ft_pwd(char **env);
t_list		*envp_to_list(char **envp);
char		**list_to_envp(t_list *env);
char		*get_env_var(char *search, t_list *lst_env);

#include "path.h"
#include "pipe.h"

#endif
