/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:06:18 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/26 09:47:07 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_name(t_token *tok, t_managparse *manag, char *result)
{
	char	*tmp;

	tmp = ft_strjoin(result, tok->name);
	if (tmp == NULL)
		malloc_fail(*tok, manag);
	free(result);
	return (tmp);
}

char	*dup_name(t_token *tok, t_managparse *manag, char *result, size_t i)
{
	char	*tmp;

	tmp = ft_strdup(&tok->name[i + 1]);
	if (tmp == NULL)
		malloc_fail(*tok, manag);
	free(tok->name);
	return (tmp);
}

char	*dbl_join(t_token *tok, t_managparse *manag, char *var, size_t ret)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(tok->name, var);
	if (tmp == NULL)
		malloc_fail(*tok, manag);
	tmp2 = ft_strjoin(tmp, &tok->name[ret]);
	free(tmp);
	if (tmp2 == NULL)
		malloc_fail(*tok, manag);
	free(tok->name);
	return (tmp2);
}

char	*var_to_replace(t_token *tok, t_managparse *manag, char *tmp)
{
	char	*var;

	if (tmp[0] == '?')
	{
		var = ft_itoa(manag->spipe->last_ret);
		if (var == NULL)
			malloc_fail(*tok, manag);
	}
	else
	{
		var = get_env(tmp);
		if (var == NULL)
			var = "";
	}
	return (var);
}

int		remove_char(char **s, size_t here)
{
	char	*result;
	char	*base;
	size_t	i;

	i = 0;
	result = ft_calloc(ft_strlen(*s), sizeof(char));
	if (result == NULL)
		return (1);
	base = result;
	if (result == NULL)
		*s = NULL;
	while (s[0][i])
	{
		if (i != here)
			*result++ = s[0][i];
		i++;
	}
	*result = '\0';
	free(*s);
	*s = base;
	return (0);
}
