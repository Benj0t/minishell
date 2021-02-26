/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:21:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/26 15:24:18 by psemsari         ###   ########.fr       */
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
	return(ft_strdup(get_env(name)));
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

char	*join_protect(char *str1, char *str2)
{
	char	*tmp;

	tmp = ft_strjoin(str1, str2);
	if (tmp == NULL)
		return (NULL);
	free(str1);
	return (tmp);
}

int		environnment_expander(char **result, size_t *i, t_token *tok, t_managparse *manag)
{
	char	*var;
	char	*value;
	size_t len;

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
		if (is_valid_env(var) || strcmp(var, "?") == 0)//a changer
		{
			value = ft_subvar(var, manag);
			if (value)
				*result = join_protect(*result, value);
			if (value)
				free(value);
			else
				malloc_fail(*tok, manag);
		}
		free(var);
	}
	else
		add_char(result, i, tok, manag);
	return (1);
}

void	simple_quote(char **result, size_t *i, t_token *tok, t_managparse *manag)
{
	(*i)++;
	while (tok->name[*i] != '\'')
	{
		add_char(result, i, tok, manag);
		(*i)++;
	}
}

int		double_quote(char **result, size_t *i, t_token *tok, t_managparse *manag)
{
	(*i)++;
	while (tok->name[*i] != '"')
	{
		if (tok->name[*i] == '\\')
			remove_backslash(result, i, tok, manag);
		else if (tok->name[*i] == '$')
			environnment_expander(result, i, tok, manag);
		else
			add_char(result, i, tok, manag);
		(*i)++;
	}
	return (0);
}

int		quote_exp(char **result, size_t *i, t_token *tok, t_managparse *manag)
{
	if (tok->name[*i] == '\'')
		simple_quote(result, i, tok, manag);
	if (tok->name[*i] == '"')
		double_quote(result, i, tok, manag);
	return (1);
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

void		add_char(char **result, size_t *i, t_token *tok, t_managparse *manag)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(*result);
	tmp = malloc(len + 1 + 1);
	ft_strcpy(tmp, *result);
	tmp[len] = tok->name[*i];
	tmp[len + 1] = '\0';
	free(*result);
	*result = tmp;
}

void		remove_backslash(char **result, size_t *i, t_token *tok, t_managparse *manag)
{
	(*i)++;
	add_char(result, i, tok, manag);
}

void		remove_backslash_check(char **result, size_t *i, t_token *tok, t_managparse *manag)
{
	if ((tok->name[*i + 1] == '$') || (tok->name[*i + 1] == '"')
		|| (tok->name[*i + 1] == '\'') || (tok->name[*i + 1] == '\\'))
		(*i)++;
	else
		(*i)++;
	add_char(result, i, tok, manag);
}

int		expansion(t_token *tok, t_managparse *manag)
{
	char	*result;
	int		env_sub;
	int		quote_sub;
	size_t	i;

	i = 0;
	env_sub = 0;
	quote_sub = 0;
	result = ft_strdup("");
	while (tok->name[i] != '\0')
	{
		if (is_quote(tok->name[i]))
			quote_sub = quote_exp(&result, &i, tok, manag);
		else if (tok->name[i] == '\\')
			remove_backslash_check(&result, &i, tok, manag);
		else if (tok->name[i] == '$')
			env_sub = environnment_expander(&result, &i, tok, manag);
		else
			add_char(&result, &i, tok, manag);
		i++;
	}
	free(tok->name);
	tok->name = result;
	if (quote_sub == 0 && env_sub == 1 && !ft_strncmp(result, "", 2))
		return (-1);
	return (env_sub);
}
