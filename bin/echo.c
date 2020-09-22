/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:37:52 by psemsari          #+#    #+#             */
/*   Updated: 2020/09/22 16:44:18 by psemsari         ###   ########.fr       */
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

int		main(int ac, char **av)
{
	int		option;
	int		i;

	option = 0;
	i = 1;
	if (ft_strncmp(av[1], "-n", ft_strlen(av[1])) == 0)
	{
		option = 1;
		i = 2;
	}
	while (av[i] != NULL)
	{
		ft_putstr(av[i]);
		i++;
	}
	if (option == 0)
		ft_putstr("\n");
	return (0);
}
