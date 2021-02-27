/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_expander.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:40:30 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/27 10:45:57 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_subvar(char *name, t_managparse *manag)
{
	char	*tmp;

	if (strcmp(name, "?") == 0)
		return (ft_itoa(manag->spipe->last_ret));
	tmp = get_env(name);
	if (tmp == NULL)
		return (ft_strdup(""));
	return (ft_strdup(get_env(name)));
}

int		get_len(char *str)
{
	size_t len;

	len = 0;
	if (ft_isdigit(str[len]))
		return (1);
	while ((ft_isalnum(str[len])) || (str[len] == '_'))
		len++;
	return (len);
}

char	*get_value(char *str, size_t *i)
{
	char	*name;
	size_t	len;
	size_t	start;

	name = NULL;
	len = 0;
	start = *i + 1;
	if (str[start + len] == '?')
		len++;
	else
		len = get_len(&str[start]);
	if (len)
	{
		name = ft_substr(str, start, len);
		*i += len;
		return (name);
	}
	return (NULL);
}

void	environnment_join(char *value, char **result,\
		t_token *tok, t_managparse *manag)
{
	if (value)
		*result = join_protect(*result, value);
	if (value)
		free(value);
	else
		malloc_fail(*tok, manag);
}

int		environnment_expander(char **result, size_t *i,\
		t_token *tok, t_managparse *manag)
{
	char	*var;
	char	*value;
	size_t	len;

	var = NULL;
	value = NULL;
	if (is_quote(tok->name[*i + 1]))
	{
		add_char(result, i, tok, manag);
		return (0);
	}
	len = get_len(tok->name);
	var = get_value(tok->name, i);
	if (var)
	{
		if (is_valid_env(var) || ft_strcmp(var, "?") == 0)
			value = ft_subvar(var, manag);
		environnment_join(value, result, tok, manag);
		free(var);
	}
	else
		add_char(result, i, tok, manag);
	return (1);
}
