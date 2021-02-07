/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:21:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/07 20:33:47 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

//quand $ expander -> transform $ en phrase
// phrase passe dans la moulinette mais ca perd tout les mecanisme

//$ ' " <>| ;
//annule la commande en le faisant disparaitre
void	backslash(char **str, t_token *tok)
{
	t_token after;

	*tok = next_token(str);
	after = next_token(str);
	if (after.type != tok_space && after.type != tok_tab)
	{
		after.name = ft_strjoin(tok->name, after.name);
		*tok = after;
	}
	// t_token tmp;

	// *tok = next_token(str);
	// tok->type = tok_word;
	// if (**str != ' ' && **str != '	')
	// {
	// 	tmp = next_token(str);
	// 	tok->name = ft_strjoin(tok->name, tmp.name);
	// }
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

// ok j'ai une bete d'idee que tu feras apres manger ...
// en fait les expander vont prendre les next arg et soit modifer le type du tok envoye soit modifier le tok et c'est comme ca que ca va changer ... on peut essayer pour backslash
// si c'est une erreur on envoie le token error ! je compte sur toi
int		environnment_expander(t_token *tok, t_list *env, s_pipe *spipe)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = 0;
	while (tok->name[i] != '\0')
	{
		if (tok->name[i] == '\'')
			quote = !quote;
		if (tok->name[i] == '$' && !quote && valid_env(&tok->name[i + 1]))
			i = ft_subvar(i, tok, env, spipe);
		i++;
	}
	if (tok->name[0] == '\0')
		return (0);
	return (1);
}

void	smplquote_expander(char **result, t_token *tok)
{
	size_t i;

	i = 0;
	while (tok->name[i] != '\'')
		i++;
	tok->name[i] = '\0';
	*result = ft_strjoin(*result, tok->name);
	tok->name = &tok->name[i+1];
}

void	dblquote_expander(char **result, t_token *tok, t_list *env, s_pipe *spipe)
{
	size_t i;
	int		backslash;

	i = 0;
	while (tok->name[i] != '"')
		i++;
	tok->name[i] = '\0';
	*result = ft_strjoin(*result, tok->name);
	tok->name = &tok->name[i+1];
}

int		expansion(t_command *command, t_token *tok, t_list *env, s_pipe *spipe)
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
			tok->name = ft_strdup(&tok->name[i + 1]); //free
			if (quote == '"')
				dblquote_expander(&result, tok, env, spipe);
			else
				smplquote_expander(&result, tok);
		}
		i++;
	}
	tok->name = ft_strjoin(result, tok->name); //free
	return (1);
}
