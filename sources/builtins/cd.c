/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:43:48 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/05 14:43:48 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	EXPAND
//	'..' = If ‘..’ appears in directory, it is processed by removing the immediately preceding pathname component, back to a slash or the beginning of directory.
//	'-' = If directory is ‘-’, it is converted to $OLDPWD before the directory change is attempted.
//	OUTPOUT
//	If a non-empty directory name from CDPATH is used, or if ‘-’ is the first argument, and the directory change is successful,
//	the absolute pathname of the new working directory is written to the standard output.
//	RETURN
//	The return status is zero if the directory is successfully changed, non-zero otherwise.
//	$CDPATH
//	If the shell variable CDPATH exists, it is used as a search path:
//	each directory name in CDPATH is searched for directory, with alternative directory names in CDPATH separated by a colon (‘:’).
//	If directory begins with a slash, CDPATH is not used.

//	Any additional arguments following directory are ignored
//	first is / -> absolute : else -> relatif
//	is '-' -> replace by $OLDPWD : else error "NO_OLDPWD"
//	nothing arg -> $HOME : else error "NO_HOME"
//	- not alone = error "NO_OPT"
//	dont work = error "NO_FILE"
//	error return 1
//	symbolic link

//	STRAT
//	detect '-'
//	complete all expansion '-' or pwd if is relative or $HOME if cd
//	if '..' or '.' -> removing

#include "minishell.h"

#define EHOME "pas de variable d'environnement $HOME"
#define EOLDPWD "pas de variable d'environnement $OLDPWD"

int		ft_cd(char **arg, t_list *env)
{
	char	*previous;
	char	*home;
	char	*pwd;
	char	*new;
	int		ret;

	errno = 0;
	pwd = getcwd(NULL, MAXPATHLEN);
	previous = get_env_var("OLDPWD", env);
	home = get_env_var("HOME", env);
	if (arg[1] == NULL)
	{
		if (home)
			new = home;
		else
		{
			ft_putstr_fd(EHOME, 2); //exit error
			return (-1);
		}
	}
	else if (!ft_strncmp(arg[1], "-", 2))
	{
		if (previous)
			new = previous;
		else
		{
			ft_putstr_fd(EOLDPWD, 2); //exit error
			return (-1);
		}
	}
	else
		new = arg[1];
	ret = chdir(new);
	if (ret != 0)
		printf("%d : %d : %s\n", ret, errno, strerror(errno));
	if (ft_strncmp(pwd, new, MAXPATHLEN))
		set_env_var("OLDPWD", pwd, env);
	return (0);
}
