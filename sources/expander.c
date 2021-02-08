/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:21:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/08 15:38:10 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

int		backslash(char *str, size_t i)
{
	if (i > 0 && str[i - 1] == '\\')
		return (1);
	return (0);
}

size_t	ft_subvar(size_t i, t_token *tok, t_list *env, s_pipe *spipe)
{
	size_t	ret;
	char	*tmp;
	char	*var;

	tok->name[i] = '\0';
	ret = 0;
	while (tok->name[i + 1 + ret])
	{
		if (!ft_isalnum(tok->name[i + 1 + ret]) && tok->name[i + 1 + ret] != '_')
			break;
		ret++;
	}
	tmp = ft_substr(&tok->name[i + 1], 0, ret);
	var = get_env_var(tmp, env);
	if (var == NULL)
		var = "";
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
		if (tok->name[i] == '$' && quote == 1 && check_env(&tok->name[i + 1]))
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

int		expansion(t_token *tok, t_list *env, s_pipe *spipe)
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
			tok->name = &tok->name[i + 1];
			i = 0;
			while (tok->name[i] != quote || backslash(tok->name, i))
				i++;
			tok->name[i] = '\0';
			result = ft_strjoin(result, tok->name);
			tok->name = &tok->name[i + 1];
			i = 0;
		}
		i++;
	}
	result = ft_strjoin(result, tok->name);
	tok->name = result;
	return (1);
}
