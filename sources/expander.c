/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:21:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/25 22:19:07 by psemsari         ###   ########.fr       */
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

char	*quote_exp(char *result, size_t *i, t_token *tok, t_managparse *manag)
{
	if (tok->name[*i] == '\'')
		simple_quote(result, i, tok, manag);
	if (tok->name[*i] == '"')
		double_quote(result, i, tok, manag);


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

void		add_char(char **result, size_t *i, t_token *tok, t_managparse *manag)
{
	char	*tmp;

	free(*result);
	tmp = ft_calloc(ft_strlen(*result) + 1, sizeof(char));
	ft_strlcpy(tmp, *result, ft_strlen(*result));
	tmp[ft_strlen(*result) - 1] = tok->name[*i];
	tmp[ft_strlen(*result)] = '\0';
	free(*result);
	result = tmp;
}

void		remove_backslash(char **result, char *tok_word, size_t *i, bool check_special)
{
	if (check_special)
	{
		if ((tok_word[*i + 1] == '$') || (tok_word[*i + 1] == '"')
			|| (tok_word[*i + 1] == '\'') || (tok_word[*i + 1] == '\\'))
			(*i)++;
	}
	else
		(*i)++;
	*result = ft_append_char(*result, tok_word + *i, true);
}

int		expansion(t_token *tok, t_managparse *manag)
{
	char	*result;
	size_t	i;

	i = 0;
	result = ft_strdup("");
	while (tok->name[i] != '\0')
	{
		if (is_quote(tok->name[i]))
			quote_exp(&result, &i, tok, manag);
		else if (tok->name[i] == '\\')
			remove_backslash(&result, &i, tok, manag);
		else if (tok->name[i] == '$')
			ft_subvar(&result, &i, tok, manag);
		else
			add_char(&result, &i, tok, manag);
		i++;
	}
	










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
