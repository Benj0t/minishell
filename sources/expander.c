/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:21:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/24 16:19:07 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_subvar(t_token *tok, t_managparse *manag, size_t i)
{
	size_t	ret;
	char	*tmp;
	char	*tmp2;
	char	*var;

	tok->name[i] = '\0';
	ret = 1;
	while (tok->name[i + 1 + ret] && tok->name[i + 1] != '?' \
		&& !ft_isdigit(tok->name[i + 1]))
	{
		if (!ft_isalnum(tok->name[i + 1 + ret]) \
			&& tok->name[i + 1 + ret] != '_')
			break ;
		ret++;
	}
	tmp = ft_substr(&tok->name[i + 1], 0, ret);
	if (tmp == NULL)
		malloc_fail(*tok, manag);
	var = var_to_replace(tok, manag, tmp);
	free(tmp);
	ret = i + 1 + ret;
	tok->name = dbl_join(tok, manag, var, ret);
	return (i + ft_strlen(var));
}

int		environnment_expander(t_token *tok, t_managparse *manag)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = 1;
	while (tok->name[i] != '\0')
	{
		if (tok->name[i] == '\'' && !backslash(tok->name, i))
			quote *= -1;
		if (tok->name[i] == '$' && quote == 1 && check_env(&tok->name[i + 1]) \
			&& !backslash(tok->name, i))
		{
			i = ft_subvar(tok, manag, i);
			continue ;
		}
		i++;
	}
	if (tok->name[0] == '\0')
		return (0);
	return (1);
}

char	*quote_exp(t_token *tok, t_managparse *manag, char *result, size_t *i)
{
	char	quote;

	quote = tok->name[*i];
	tok->name[*i] = '\0';
	result = join_name(tok, manag, result);
	tok->name = dup_name(tok, manag, result, *i);
	*i = 0;
	while (tok->name[*i] != '\0')
	{
		*i = backslash_quote(tok, *i, quote);
		(*i)++;
	}
	tok->name[*i] = '\0';
	result = join_name(tok, manag, result);
	tok->name = dup_name(tok, manag, result, *i);
	*i = 0;
	return (result);
}

int		expansion(t_token *tok, t_managparse *manag)
{
	char	*result;
	size_t	i;

	i = 0;
	result = ft_strdup("");
	if (result == NULL)
		malloc_fail(*tok, manag);
	while (tok->name[i] != '\0')
	{
		if (is_quote(tok->name[i]) && !backslash(tok->name, i))
			result = quote_exp(tok, manag, result, &i);
		i++;
	}
	result = join_name(tok, manag, result);
	free(tok->name);
	tok->name = result;
	return (1);
}

int		backslash_remove(t_token *tok, t_managparse *manag)
{
	char	*result;
	char	quote;
	int		blvl;
	size_t	i;

	i = 0;
	while (tok->name[i] != '\0')
	{
		while (tok->name[i] == '\\')
				i++;
		if ((tok->name[i] == '"' || tok->name[i] == '\'') \
			&& !backslash(tok->name, i))
		{
			quote = tok->name[i];
			i++;
			while (tok->name[i] != quote || (tok->name[i] == quote && backslash(tok->name, i)))
				i++;
			i++;
			continue ;
		}
		blvl = backslash_lvl(tok->name, i);
		if ((blvl % 2) == 1 || blvl == 1)
			blvl = (blvl / 2) + 1;
		else
			blvl = blvl / 2;
		while (blvl)
		{
			remove_char(&tok->name, i - 1);
			blvl--;
			i--;
		}
		i++;
	}
	return (1);
}
