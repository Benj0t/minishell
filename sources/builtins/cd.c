/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 14:43:48 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/22 19:34:34 by bemoreau         ###   ########.fr       */
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

char			*ft_joinpath(char const *s1, char const *s2)
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

int				wrong_file(int *bool, int *ret, char **pwd, char **arg)
{
	if (*pwd == NULL)
	{
		if ((*ret = chdir(arg[1]) == -1 && getcwd(NULL, MAXPATHLEN) == NULL)\
									|| ft_strncmp(arg[1], ".", 2) == 0)
		{
			ft_putstr_fd("Can't find current working directory\n", 2);
			return (1);
		}
		*bool = 1;
		*pwd = getcwd(NULL, MAXPATHLEN);
	}
	return (0);
}

int				ft_cd(char **arg)
{
	char		*previous;
	char		*home;
	char		*pwd;
	char		*tmp;
	char		*new;
	int			ret;
	int			bool;

	errno = 0;
	bool = 0;
	pwd = getcwd(NULL, MAXPATHLEN);
	if (wrong_file(&bool, &ret, &pwd, arg) == 1)
		return (1);
	previous = get_env("OLDPWD");
	home = get_env("HOME");
	if (arg[1] == NULL)
	{
		if (home)
			new = home;
		else
			return (cd_error(EHOME));
	}
	else if (!ft_strncmp(arg[1], "-", 2))
	{
		if (previous)
			new = previous;
		else
			return (cd_error(EOLDPWD));
	}
	else
		new = arg[1];
	if (!bool)
		ret = chdir(new);
	tmp = getcwd(NULL, MAXPATHLEN);
	if (tmp != NULL)
		set_env("PWD", tmp, 1);
	if (ret != 0)
		return (cd_error(NULL));
	if (ft_strncmp(pwd, new, MAXPATHLEN))
		set_env("OLDPWD", pwd, 1);
	return (0);
}
