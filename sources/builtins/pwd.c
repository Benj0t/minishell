/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 20:01:04 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/28 15:48:06 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "limits.h"

int		ft_pwd(void)
{
	char	*pwd;

	if ((pwd = getcwd(NULL, MAXPATHLEN)) == NULL)
	{
		pwd = get_env("PWD");
		if (pwd == NULL)
		{
			ft_putstr_fd("minishell: Could not find your cwd\n", 2);
			return (1);
		}
		ft_putstr_fd(pwd, 1);
		ft_putchar_fd('\n', 1);
		return (0);
	}
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	return (0);
}
