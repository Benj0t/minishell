/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:06:18 by psemsari          #+#    #+#             */
/*   Updated: 2021/03/01 00:45:15 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_protect(char *str1, char *str2)
{
	char	*tmp;

	tmp = ft_strjoin(str1, str2);
	if (tmp == NULL)
		return (NULL);
	free(str1);
	return (tmp);
}

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

void	add_char(char **result, size_t *i,\
		t_token *tok, t_managparse *manag)
{
	size_t	len;
	char	*tmp;

	(void)manag;
	len = ft_strlen(*result);
	tmp = malloc(len + 1 + 1);
	ft_strcpy(tmp, *result);
	tmp[len] = tok->name[*i];
	tmp[len + 1] = '\0';
	free(*result);
	*result = tmp;
}

void	remove_backslash_check(char **result, size_t *i,\
		t_token *tok, t_managparse *manag)
{
	if ((tok->name[*i + 1] == '$') || (tok->name[*i + 1] == '"')\
		|| (tok->name[*i + 1] == '\\'))
		(*i)++;
	add_char(result, i, tok, manag);
}

void	remove_backslash(char **result, size_t *i,\
		t_token *tok, t_managparse *manag)
{
	(*i)++;
	add_char(result, i, tok, manag);
}
