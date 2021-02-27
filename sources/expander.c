/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:21:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/27 23:45:57 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_quote(char **result, size_t *i,\
		t_token *tok, t_managparse *manag)
{
	(*i)++;
	while (tok->name[*i] != '\'')
	{
		add_char(result, i, tok, manag);
		(*i)++;
	}
}

int		double_quote(char **result, size_t *i,\
	t_token *tok, t_managparse *manag)
{
	(*i)++;
	while (tok->name[*i] != '"')
	{
		if (tok->name[*i] == '\\')
			remove_backslash_check(result, i, tok, manag);
		else if (tok->name[*i] == '$')
		{
			manag->is_in_quote = 1;
			environnment_expander(result, i, tok, manag);
		}
		else
			add_char(result, i, tok, manag);
		(*i)++;
	}
	return (0);
}

int		quote_exp(char **result, size_t *i,\
	t_token *tok, t_managparse *manag)
{
	if (tok->name[*i] == '\'')
		simple_quote(result, i, tok, manag);
	if (tok->name[*i] == '"')
		double_quote(result, i, tok, manag);
	return (1);
}

void	replace(t_token *tok, char *result, int env_sub, int quote_sub)
{
	free(tok->name);
	tok->name = result;
	if (quote_sub == 0 && env_sub == 1 && !ft_strcmp(result, ""))
	{
		free(tok->name);
		tok->name = NULL;
	}
}

int		expansion(t_token *tok, t_managparse *manag, size_t i)
{
	char	*result;
	int		env_sub;
	int		quote_sub;

	env_sub = 0;
	quote_sub = 0;
	result = ft_strdup("");
	while (tok->name[i] != '\0')
	{
		if (is_quote(tok->name[i]))
			quote_sub = quote_exp(&result, &i, tok, manag);
		else if (tok->name[i] == '\\')
			remove_backslash(&result, &i, tok, manag);
		else if (tok->name[i] == '$')
		{
			manag->is_in_quote = 0;
			env_sub = environnment_expander(&result, &i, tok, manag);
		}
		else
			add_char(&result, &i, tok, manag);
		i++;
	}
	replace(tok, result, env_sub, quote_sub);
	return (env_sub);
}
