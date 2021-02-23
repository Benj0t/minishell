/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 20:01:04 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/23 12:52:40 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "limits.h"

int		ft_pwd(void)
{
	char	*pwd;

	pwd = get_env("PWD");
	if (pwd == NULL)
		return (-1);
	else
		ft_putstr_fd(pwd, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}
