/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:21:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/30 15:59:41 by psemsari         ###   ########.fr       */
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

// ok j'ai une bete d'idee que tu feras apres manger ...
// en fait les expander vont prendre les next arg et soit modifer le type du tok envoye soit modifier le tok et c'est comme ca que ca va changer ... on peut essayer pour backslash
// si c'est une erreur on envoie le token error ! je compte sur toi
void	environnment_expander(char **str, t_token *tok, t_list *env, s_pipe *spipe)
{
	size_t	i;
	char	*ret;
	char	*key;
	char	*var;

	i = 0;
	while (tok->name[i] != ' ' && tok->name[i] != '	' && tok->name[i] != '\0' && tok->name[i] != '"' && tok->name[i] != '\\')
		i++;
	//pour le test de char
	key = ft_substr(tok->name, 0, i);
	var = get_env_var(key, env);
	if (var == NULL)
		var = "";
	*str = ft_strjoin(*str, var);
	tok->name = ft_strdup(&tok->name[i]);
}

void	smplquote_expander(char **result, t_token *tok)
{
	size_t i;

	i = 0;
	while (tok->name[i] != '"')
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
	{
		backslash = 0;
		if (tok->name[i] == '\\' && tok->name[i+1] == '$')
		{
			backslash = 1;
			tok->name[i] = '\0';
			*result = ft_strjoin(*result, tok->name);
			tok->name = ft_strdup(&tok->name[i + 1]);
			i++;
		}
		if (tok->name[i] == '$' && !backslash)
		{
			tok->name[i] = '\0';
			*result = ft_strjoin(*result, tok->name);
			tok->name = ft_strdup(&tok->name[i + 1]);
			environnment_expander(result, tok, env, spipe);
			i = 0;
			continue;
		}
		i++;
	}
	tok->name[i] = '\0';
	*result = ft_strjoin(*result, tok->name);
	tok->name = &tok->name[i+1];
}

void	expansion(t_token *tok, t_list *env, s_pipe *spipe)
{
	char	*result;
	size_t	i;

	i = 0;
	result = ft_strdup("");
	while (tok->name[i] != '\0')
	{
		if (is_quote(tok->name[i]))
		{
			tok->name[i] = '\0';
			result = ft_strjoin(result, tok->name);
			tok->name = ft_strdup(&tok->name[i + 1]); //free
			dblquote_expander(&result, tok, env, spipe);
		}
		if (tok->name[i] == '$')
		{
			tok->name[i] = '\0';
			result = ft_strjoin(result, tok->name);
			tok->name = ft_strdup(&tok->name[i + 1]);
			environnment_expander(&result, tok, env, spipe);
			i = 0;
			continue;
		}
		i++;
	}
	tok->name = ft_strjoin(result, tok->name); //free
}
