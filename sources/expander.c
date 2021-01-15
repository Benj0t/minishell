/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:21:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/15 17:37:25 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

//quand $ expander -> transform $ en phrase
// phrase passe dans la moulinette mais ca perd tout les mecanisme

void	ft_replace(char **str, char *search, char *replace) //expander
{
	size_t	i;
	char	*retstr;
	char	*tmp;
	char	*ret;

	i = 0;
	retstr = ft_strnstr(str[0], search, ft_strlen(str[0]));
	retstr[0] = '\0';
	tmp = ft_strjoin(str[0], replace);
	retstr[0] = '$';
	ret = ft_strjoin(tmp, &retstr[ft_strlen(search)]);
	free(tmp);
	free(*str);
	*str = ret;
}

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
	if (str[0][i] == T_EOF)
		return ;
	tok->name = ft_substr(*str, 0, i);
	*str = ft_strdup(&str[0][i + 1]); //free
}

void	dblquote_expander(char **str, t_token *tok, t_list *env)
{
	size_t	i;

	i = 0;
	while (str[0][i] != T_ALL[2] && str[0][i] != T_EOF)
	{
		i++;
	}
	if (str[0][i] == T_EOF) //erreur
		return ;
	tok->name = ft_substr(*str, 0, i);
	*str = ft_strdup(&str[0][i + 1]); //free
	return ;
}
