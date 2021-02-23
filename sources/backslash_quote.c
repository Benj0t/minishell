/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:00:04 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/23 19:50:41 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		backslash_lvl(char *str, size_t i)
{
	int		lvl;

	lvl = 0;
	i--;
	while (str[i] == '\\' && i > 0)
	{
		lvl++;
		i--;
	}
	if (str[i] == '\\' && i == 0)
		lvl++;
	return (lvl);
}

void	backslash_quote(t_token *tok, size_t *i, char quote)
{
	int blvl;

	blvl = 0;
	if (quote == '"' && (tok->name[*i] == '$' || tok->name[*i] == '"' \
		|| (tok->name[*i] == '\\' && tok->name[*i + 1] != '\\' \
		&& tok->name[*i + 1] != '$' && tok->name[*i + 1] != '"')))
	{
		blvl = backslash_lvl(tok->name, *i);
		if (tok->name[*i] == '\\')
			blvl++;
		if ((blvl % 2) == 0)
		{
			blvl = blvl / 2;
			if (tok->name[*i] == '"')
				remove_char(&tok->name, *i);
		}
		else
			blvl = (blvl / 2) + 1;
		while (blvl)
		{
			remove_char(&tok->name, *i - 1);
			blvl--;
			*i = *i - 1;
		}
	}
}
