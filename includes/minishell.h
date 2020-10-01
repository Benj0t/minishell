#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "parser.h"

char		*path(char **env, char *str);
t_list		*envp_to_list(char **envp);
char		*get_env_var(char *search, t_list *lst_env);

#endif
