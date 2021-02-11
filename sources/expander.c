/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:21:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/11 15:42:23 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int		backslash(char *str, size_t i)
{
	if (i > 0 && str[i - 1] == '\\')
	{
		if (backslash(str, i - 1))
			return (0);
		return (1);
	}
	return (0);
}

size_t	ft_subvar(size_t i, t_token *tok, t_list *env, s_pipe *spipe)
{
	size_t	ret;
	char	*tmp;
	char	*var;

	tok->name[i] = '\0';
	ret = 1;
	while (tok->name[i + 1 + ret] && tok->name[i + 1] != '?' && !ft_isdigit(tok->name[i + 1]))
	{
		if (!ft_isalnum(tok->name[i + 1 + ret]) && tok->name[i + 1 + ret] != '_')
			break;
		ret++;
	}
	tmp = ft_substr(&tok->name[i + 1], 0, ret);
	if (tmp[0] == '?')
		var = ft_itoa(spipe->last_ret);
	else
	{
		var = get_env_var(tmp, env);
		if (var == NULL)
			var = "";
	}
	free(tmp);
	tmp = ft_strjoin(tok->name, var);
	tok->name = ft_strjoin(tmp, &tok->name[i + 1 + ret]);
	free(tmp);
	return (i + ft_strlen(var));
}

int		environnment_expander(t_token *tok, t_list *env, s_pipe *spipe)
{//a faire $?
	size_t	i;
	int		quote;

	i = 0;
	quote = 1;
	while (tok->name[i] != '\0')
	{
		if (tok->name[i] == '\'')
			quote *= -1;
		if (tok->name[i] == '$' && quote == 1 && check_env(&tok->name[i + 1]) && !backslash(tok->name, i))
		{
			i = ft_subvar(i, tok, env, spipe);
			continue ;
		}
		i++;
	}
	if (tok->name[0] == '\0')
		return (0);
	return (1);
}

void	add_char(char **s, size_t here)
{
	char	*result;
	char	*base;
	size_t	i;

	i = 0;
	result = ft_calloc(ft_strlen(*s) + 1, sizeof(char));
	base = result;
	if (result == NULL)
		*s = NULL;
	while (s[0][i])
	{
		if (i == here)
			*result++ = '\\';
		*result++ = s[0][i];
		i++;
	}
	*result = '\0';
	free(*s);
	*s = base;
}

void	remove_char(char **s, size_t here)
{
	char	*result;
	char	*base;
	size_t	i;

	i = 0;
	result = ft_calloc(ft_strlen(*s), sizeof(char));
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
}

int		expansion(t_token *tok)
{
	char	*result;
	char	quote;
	size_t	i;

	i = 0;
	result = ft_strdup("");
	while (tok->name[i] != '\0')
	{
		if (is_quote(tok->name[i]))
		{
			quote = tok->name[i];
			tok->name[i] = '\0';
			result = ft_strjoin(result, tok->name);
			tok->name = ft_strdup(&tok->name[i + 1]);
			i = 0;
			while (tok->name[i] != quote || backslash(tok->name, i))
				i++;
			tok->name[i] = '\0';
			result = ft_strjoin(result, tok->name);
			tok->name = ft_strdup(&tok->name[i + 1]);
			i = 0;
		}
		i++;
	}
	result = ft_strjoin(result, tok->name);
	tok->name = result;
	return (1);
}

int		backslash_remove(t_token *tok)
{
	char	*result;
	char	quote;
	size_t	i;

	i = 0;
	while (tok->name[i] != '\0')
	{
		if (tok->name[i] == '"')
		{
			i++;
			while (tok->name[i] != '"')
				i++;
			i++;
		}
		if (tok->name[i] == '\\' && quote != '\'')
		{
			if (tok->name[i + 1] == '\\')
				remove_char(&tok->name, i + 1);
			else
				remove_char(&tok->name, i);
		}
		i++;
	}
	return (1);
}
