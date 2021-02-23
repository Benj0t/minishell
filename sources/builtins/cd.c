/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:43:48 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/22 21:25:26 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int				ft_cd(char **arg)
{
	char	*previous;
	char	*home;
	char	*pwd;
	char	*new;
	int		ret;

	errno = 0;
	pwd = getcwd(NULL, MAXPATHLEN);
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
	ret = chdir(new);
	if (ret != 0)
		return (cd_error(NULL));
	if (ft_strncmp(pwd, new, MAXPATHLEN))
		setenv("OLDPWD", pwd, 1);
	return (0);
}
