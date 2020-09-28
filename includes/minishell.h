#ifndef MINISHELL_H
# define MINISHELL_H

<<<<<<< HEAD
# include "libft.h"
=======
# include "../sources/libft/libft.h"
>>>>>>> 4b3fda8431a25f107afbf0e43c6a8cd71671195e
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
<<<<<<< HEAD
# include <signal.h>
# include "parser.h"

char		*path(char **env, char *str);

#endif
=======

char        *path(char **env);

#endif
>>>>>>> 4b3fda8431a25f107afbf0e43c6a8cd71671195e
