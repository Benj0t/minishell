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
# include <sys/stat.h>

char		*ft_path(char **env, char *str);
int			ft_pipe(char **env, char *command1, char *command2);

#endif
