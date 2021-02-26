/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:00:04 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/26 09:48:00 by psemsari         ###   ########.fr       */
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

// size_t	backslash_quote(t_token *tok, size_t i, char quote)
// {
// 	int blvl;

// 	blvl = 0;
// 	if (tok->name[i] == '\\')
// 	{
// 		while (tok->name[i] == '\\')
// 			i++;
// 		blvl = backslash_lvl(tok->name, i);
// 		if (tok->name[i] == '\\')
// 			blvl++;
// 		blvl = blvl / 2;
// 		while (blvl)
// 		{
// 			remove_char(&tok->name, i - 1);
// 			blvl--;
// 			i = i - 1;
// 		}
// 		if (tok->name[i] == '"' || tok->name[i] == '$')
// 			remove_char(&tok->name, i - 1);
// 	}
// 	return (i);
// }
