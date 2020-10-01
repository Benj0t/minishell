/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:16:26 by psemsari          #+#    #+#             */
/*   Updated: 2020/10/01 20:55:17 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replace(char **str, char *search, char *replace)
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

char	*arg_except(char **str, char *ret, t_list *env)
{
	size_t	i;
	char	c;
	char	*env_key;
	char	*env_var;
	char	*tmp;

	i = 0;
	c = ret[0];
	free(ret);
	while (str[0][i] != c && str[0][i] != '\0')
	{
		if (str[0][i] == '$' && c == '"')
		{	//voir $?
			env_key = ft_substr(&str[0][i], 0, next_space(&str[0][i]));
			if ((env_var = get_env_var(&env_key[1], env)) != NULL)
				ft_replace(str, env_key, env_var);
			free(env_key);
			//env_var == null error
			i = i + ft_strlen(env_var) - 1;
		}
		i++;
	}
	if (str[0][i] == c)
	{
		ret = (char *)malloc(i + 1);
		ft_strlcpy(ret, *str, i + 1);
		tmp = ft_strdup(&str[0][i + 1]);
		free(*str);
		*str = tmp;
		return (ret);
	}
	return (NULL); //quote not close error
}

char	*next_arg(char **str)
{
	size_t	i;
	size_t	i2;
	char	*ret;
	char	*tmp;

	i = 0;
	if (str[0][i] == '\0')
		return (NULL);
	while ((str[0][i] == ' ' || str[0][i] == '	') && str[0][i] != '\0')
		i++;
	tmp = ft_strdup(&str[0][i]);
	free(*str);
	*str = tmp;
	i = 0;
	while (str[0][i] != '	' && str[0][i] != ' ' && str[0][i] != '"'
	&& str[0][i] != '\'' && str[0][i] != '<' && str[0][i] != '>'
	&& str[0][i] != ';' && str[0][i] != '|' && str[0][i] != '$'
	&& str[0][i] != '\0')
		i++;
	if (i == 0)
	{
		ret = (char *)malloc(2);
		ft_strlcpy(ret, *str, 2);
		tmp = ft_strdup(&str[0][1]);
		free(*str);
		*str = tmp;
	}
	else
	{
		ret = (char *)malloc(i + 1);
		ft_strlcpy(ret, *str, i + 1);
		tmp = ft_strdup(&str[0][i]);
		free(*str);
		*str = tmp;
	}
	return (ret);
}

char	*arg_env(char **str, char *ret, t_list *lst_env)
{
	char	*search;
	//voir $?
	search = next_arg(str);
	free(ret);
	return (ft_strdup(get_env_var(search, lst_env)));
}

int		parser(char *str, t_list *env)
{
	t_list		*lst_pipe;
	t_list		*lst_redi;
	t_parser	parsing;
	size_t		i;
	char		*ret;

	i = 0;
	str = ft_strdup(str);
	printf("-%s-\n", str);
	while ((ret = next_arg(&str)) != NULL)
	{
		if (ret[0] == '\"' || ret[0] == '\'')
			ret = arg_except(&str, ret, env);
		else if (ret[0] == '$')
			ret = arg_env(&str, ret, env);
		printf("-%s- | -%s-\n", ret, str);
		free(ret);
		sleep(1);
	}
	free(str);
	return (0);
}
