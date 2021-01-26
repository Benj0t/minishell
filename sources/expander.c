/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:21:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/26 15:56:50 by psemsari         ###   ########.fr       */
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

}

void	smplquote_expander(char **result, t_token *tok)
{
	size_t i;

	i = 0;
	while (tok->name[i] != '"')
	{
		i++;
	}
	*result = ft_strjoin(*result, ft_substr(tok->name, 0, i));
	tok->name = ft_strdup(&tok->name[i + 1]); //free
}

void	dblquote_expander(char **result, t_token *tok, t_list *env, s_pipe *spipe)
{
	size_t i;

	i = 0;
	while (tok->name[i] != '"')
	{
		if (tok->name[i] == '$')
			environnment_expander(result, tok, env, spipe);
		i++;
	}
	*result = ft_strjoin(*result, ft_substr(tok->name, 0, i));
	tok->name = ft_strdup(&tok->name[i + 1]); //free
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
			result = ft_substr(tok->name, 0, i);
			tok->name = ft_strdup(&tok->name[i + 1]); //free
			dblquote_expander(&result, tok, env, spipe);
		}
		i++;
	}
	tok->name = ft_strjoin(result, tok->name); //free
}
