/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:16:26 by psemsari          #+#    #+#             */
/*   Updated: 2020/09/30 18:35:11 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// cat lol.c ;

char	*arg_env(char *str, t_list *lst_env)
{
	t_var_env *env;
	env = (t_var_env *)lst_env->content;
	while (ft_strncmp(env->key, str, ft_strlen(str)) && lst_env != NULL)
	{
		lst_env->next = lst_env;
		env = (t_var_env *)lst_env->content;
	}
	return (env->var);
}

char	*arg_except(char **str, char *ret)
{
	size_t	i;
	char	c;

	i = 0;
	c = ret[0];
	free(ret);
	while (str[0][i] != c && str[0][i] != '\0')
		i++;
	if (str[0][i] == c)
	{
		ret = (char *)malloc(i + 1);
		ft_strlcpy(ret, *str, i + 1);
		*str = &str[0][i + 1];
		return (ret);
	}
	return (NULL);
}

char	*next_arg(char **str)
{
	size_t	i;
	size_t	i2;
	char	*ret;

	i = 0;
	if (str[0][i] == '\0')
		return (NULL);
	while ((str[0][i] == ' ' || str[0][i] == '	') && str[0][i] != '\0')
		i++;
	*str = &str[0][i];
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
		*str = &str[0][1];
	}
	else
	{
		ret = (char *)malloc(i + 1);
		ft_strlcpy(ret, *str, i + 1);
		*str = &str[0][i];
	}
	return (ret);
}

int		parser(char *str)
{
	t_list		*lst_pipe;
	t_list		*lst_redi;
	t_parser	parsing;
	size_t		i;
	char		*ret;

	i = 0;
	printf("-%s-\n", str);
	while ((ret = next_arg(&str)) != NULL)
	{
		if (ret[0] == '\"' || ret[0] == '\'')
			ret = arg_except(&str, ret);
		printf("-%s- | -%s-\n", ret, str);
		free(ret);
		sleep(1);
	}
	return (0);
}
