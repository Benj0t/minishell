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

#define EHOME "HOME not set"
#define EOLDPWD "OLDPWD not set"
#define ENOPERM "permission denied"
#define ENODIR "No such file or directory"

static int		cd_error(char *error)
{
	char *str;

	if (errno)
		str = strerror(errno);
	else
		str = error;
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

char	*ft_joinpath(char const *s1, char const *s2)
{
	char	*ptr;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!ptr)
		return (NULL);
	tmp = ptr;
	while (*s1 != '\0')
		*ptr++ = *s1++;
	*ptr++ = '/';
	while (*s2 != '\0')
		*ptr++ = *s2++;
	*ptr = '\0';
	return (tmp);
}

int				ft_cd(char **arg)
{
	char	*previous;
	char	*home;
	char	*pwd;
	char	*new;
	int		ret;
	int		bool;

	errno = 0;
	bool = 0;
	pwd = getcwd(NULL, MAXPATHLEN);
	if (pwd == NULL)
	{
		if ((ret = chdir(arg[1]) == -1 && getcwd(NULL, MAXPATHLEN) == NULL) || ft_strncmp(arg[1], ".", 2) == 0)
		{
			ft_putstr_fd("Can't find current working directory\n", 2);
			return (1);
		}
		bool = 1;
		pwd = getcwd(NULL, MAXPATHLEN);
	}
	previous = getenv("OLDPWD");
	home = getenv("HOME");
	if (arg[1] == NULL)
	{
		if (home)
			new = home;
		else
			cd_error(EHOME);
	}
	else if (!ft_strncmp(arg[1], "-", 2))
	{
		if (previous)
			new = previous;
		else
			cd_error(EOLDPWD);
	}
	else
		new = arg[1];
	if (!bool)
		ret = chdir(new);
	char *str;
	str = getcwd(NULL, MAXPATHLEN);
	if (str != NULL)
		setenv("PWD", str, 1);
	if (ret != 0)
		return (cd_error(NULL));
	if (ft_strncmp(pwd, new, MAXPATHLEN))
		setenv("OLDPWD", pwd, 1);
	return (0);
}
