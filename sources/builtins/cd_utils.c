/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 13:15:12 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/27 14:17:42 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd_error(char *error)
{
	char *str;

	if (errno)
		str = strerror(errno);
	else
		str = error;
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int		add_dot(void)
{
	char *name;
	char *tmp;

	ft_putstr_fd("Can't find current working directory\n", 2);
	tmp = get_env("PWD");
	name = ft_strjoin(tmp, "/.");
	if (name)
	{
		set_env("PWD", name, 1);
		free(name);
	}
	return (1);
}
