/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:43:57 by psemsari          #+#    #+#             */
/*   Updated: 2020/10/01 20:44:32 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	next_space(char *str)
{
	size_t	ret;

	ret = 0;
	while (str[ret] != ' ' && str[ret] != '\''
		&& str[ret] != '"' && str[ret] != '\0')
		ret++;
	return (ret);
}
