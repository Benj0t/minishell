/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 20:01:04 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/28 11:18:19 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "limits.h"

int		ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, MAXPATHLEN);
	if (pwd == NULL)
		return (-1);
	else
		ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	return (0);
}
