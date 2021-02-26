/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:00:04 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/26 15:49:07 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		backslash_lvl(char *str, size_t i)
{
	int		lvl;

	lvl = 0;
	if (i > 0)
	{
		i--;
		while (str[i] == '\\')
		{
			lvl++;
			i--;
			if (i == 0)
				break ;
		}
		if (str[i] == '\\' && i == 0)
			lvl++;
	}
	return (lvl);
}
