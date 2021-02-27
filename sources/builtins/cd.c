/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:43:48 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/27 13:17:44 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EHOME "HOME not set"
#define EOLDPWD "OLDPWD not set"
#define ENOPERM "permission denied"
#define ENODIR "No such file or directory"

int				wrong_file(int *bool, int *ret, char **pwd, char **arg)
{
	char *tmp;

	tmp = NULL;
	if (*pwd == NULL)
	{
		if ((*ret = chdir(arg[1]) == -1))
			if ((((tmp = getcwd(NULL, MAXPATHLEN)) == NULL)) ||\
									ft_strncmp(arg[1], ".", 2) == 0)
			{
				if (!ft_strncmp(arg[1], ".", 2))
					return (add_dot());
				ft_putstr_fd("Can't find current working directory\n", 2);
				return (1);
			}
		if (tmp)
			free(tmp);
		*bool = 1;
		*pwd = getcwd(NULL, MAXPATHLEN);
	}
	return (0);
}

int				get_arg(char **arg, char **new, char *previous, char *home)
{
	if (arg[1] == NULL)
	{
		if (home)
			*new = home;
		else
			return (cd_error(EHOME));
	}
	else if (!ft_strncmp(arg[1], "-", 2))
	{
		if (previous)
			*new = previous;
		else
			return (cd_error(EOLDPWD));
	}
	else
		*new = arg[1];
	return (0);
}

int				set_varenv(t_cd *cd)
{
	if (!cd->bool)
		cd->ret = chdir(cd->new);
	cd->tmp = getcwd(NULL, MAXPATHLEN);
	if (cd->tmp != NULL)
		set_env("PWD", cd->tmp, 1);
	free(cd->tmp);
	if (cd->ret != 0)
	{
		free(cd->pwd);
		return (cd_error(ENODIR));
	}
	if (!ft_strncmp(cd->previous, cd->new, MAXPATHLEN))
		ft_pwd();
	if (ft_strncmp(cd->pwd, cd->new, MAXPATHLEN))
		set_env("OLDPWD", cd->pwd, 1);
	free(cd->pwd);
	return (0);
}

int				ft_cd(char **arg)
{
	t_cd cd;

	errno = 0;
	cd.bool = 0;
	cd.pwd = getcwd(NULL, MAXPATHLEN);
	if (wrong_file(&(cd.bool), &cd.ret, &cd.pwd, arg) == 1)
		return (1);
	cd.previous = get_env("OLDPWD");
	cd.home = get_env("HOME");
	if (get_arg(arg, &cd.new, cd.previous, cd.home))
	{
		free(cd.pwd);
		return (1);
	}
	return (set_varenv(&cd));
}
