/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:21:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/18 11:37:41 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

//quand $ expander -> transform $ en phrase
// phrase passe dans la moulinette mais ca perd tout les mecanisme

void	environnment_expander(char **str, t_list *env)
{
	t_token	tok;
	char	*var;

	tok = next_token(str);
	var = get_env_var(tok.name, env);
	if (var != NULL)
		*str = ft_strjoin(var, *str); //free
}

void	smplquote_expander(char **str, t_token *tok)
{
	size_t	i;

	i = 0;
	while (str[0][i] != T_ALL[3] && str[0][i] != T_EOF)
		i++;
	if (str[0][i] == T_EOF) //erreur
		return ;
	tok->name = ft_substr(*str, 0, i);
	*str = ft_strdup(&str[0][i + 1]); //free
}

void	dblquote_expander(char **str, t_token *tok, t_list *env)
{
	t_token	tmp;
	char	*ret;
	char	*var;
	char	*name;

	tmp = next_token(str);
	ret = ft_strdup("");
	while (tmp.type != tok_dblquote && tmp.type != tok_eof)
	{
		if (tmp.type == tok_env)
			environnment_expander(str, env);
		if (tmp.type != tok_dblquote && tmp.type != tok_env)
			ret = ft_strjoin(ret, tmp.name); //free
		tmp = next_token(str);
	}
	if (tmp.type == tok_eof) //erreur
		return ;
	tok->name = ret;
	return ;
}
