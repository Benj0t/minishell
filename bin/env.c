/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 16:42:44 by psemsari          #+#    #+#             */
/*   Updated: 2020/09/22 16:48:34 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
		write(1, &(str[i++]), 1);
}

int main(int argc, char **argv, char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		ft_putstr(envp[i]);
		ft_putstr("\n");
		i++;
	}
	return (0);
}
