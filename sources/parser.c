/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:16:26 by psemsari          #+#    #+#             */
/*   Updated: 2020/10/14 16:48:23 by psemsari         ###   ########.fr       */
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
	int		i;
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
			{
				ft_replace(str, env_key, env_var);
				i = i + ft_strlen(env_var) - 1;
			}
			else
			{
				ft_replace(str, env_key, " ");
			}
			free(env_key);
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

char	*arg_next(char **str)
{
	size_t	i;
	size_t	i2;
	char	*ret;
	char	*tmp;

	i = 0;
	if (str[0][i] == '\0')
	{
		free(*str);
		*str = NULL;
		return (NULL);
	}
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
		if (tmp[0] == '\0')
		{
			free(tmp);
			*str = NULL;
		}
		else
			*str = tmp;
	}
	else
	{
		ret = (char *)malloc(i + 1);
		ft_strlcpy(ret, *str, i + 1);
		tmp = ft_strdup(&str[0][i]);
		free(*str);
		if (tmp[0] == '\0')
		{
			free(tmp);
			*str = NULL;
		}
		else
			*str = tmp;
	}
	return (ret);
}

char	*arg_env(char **str, char *ret, t_list *lst_env)
{
	char	*search;
	char	*result;
	//voir $?
	search = arg_next(str);
	free(ret);
	if (!strcmp(search, "?"))
		return (ft_strdup(ft_itoa(0))); //à voir
	result = get_env_var(search, lst_env);
	free(search);
	if (result == NULL)
		return (NULL);
	return (ft_strdup(result));
}

char	*next(char **str, t_list *env)
{
	char		*ret;

	if (*str == NULL)
		return (NULL);
	if ((ret = arg_next(str)) != NULL)
	{
		if (ret[0] == '\"' || ret[0] == '\'')
			ret = arg_except(str, ret, env);
		else if (ret[0] == '$')
			ret = arg_env(str, ret, env);
	}
	return (ret);
}

void	setup_command(t_command *ret)
{
	ret->argument = NULL;
	ret->redir_in = NULL;
	ret->redir_out = NULL;
	ret->pipe = NULL;
}

t_command	*multi_command(char **str, t_list *env)
{
	t_command	*command;
	char		*ret;

	command = malloc(sizeof(t_command));
	setup_command(command);
	ret = next(str, env);
	while (ret != NULL)
	{
		if (!ft_strncmp(ret, ">", ft_strlen(ret)))
		{
			free(ret);
			ret = next(str, env);
			ft_lstadd_back(&command->redir_out, ft_lstnew(ret));
		}
		else if (!ft_strncmp(ret, "<", ft_strlen(ret)))
		{
			free(ret);
			ret = next(str, env);
			ft_lstadd_back(&command->redir_in, ft_lstnew(ret));
		}
		else if (!ft_strncmp(ret, "|", ft_strlen(ret)))
		{
			free(ret);
			command->pipe = multi_command(str, env);
		}
		else if (!ft_strncmp(ret, ";", ft_strlen(ret)))
		{
			free(ret);
			return (command);
		}
		else
			ft_lstadd_back(&command->argument, ft_lstnew(ret));
		ret = next(str, env);
	}
	free(ret);
	return (command);
}

void		clear_multi_command(t_command *command)
{
	t_command	*tmp;

	tmp = NULL;
	while (command != NULL)
	{
		tmp = command->pipe;
		ft_lstclear(&command->argument, free);
		ft_lstclear(&command->redir_in, free);
		ft_lstclear(&command->redir_out, free);
		free(command);
		command = tmp;
	}
}

void		print_multi_command(t_command *command)
{
	while (command != NULL)
	{
		printf("COMMAND:\n");
		while (command->argument != NULL)
		{
			printf("	arg: -%s-\n", (char *)command->argument->content);
			command->argument = command->argument->next;
		}
		while (command->redir_in != NULL)
		{
			printf("	redir_in: -%s-\n", (char *)command->redir_in->content);
			command->redir_in = command->redir_in->next;
		}
		while (command->redir_out != NULL)
		{
			printf("	redir_out: -%s-\n", (char *)command->redir_out->content);
			command->redir_out = command->redir_out->next;
		}
		command = command->pipe;
	}
}

int		parser(char *str, t_list *env)
{
	t_command	*command;
	t_list		*arg;

	str = ft_strdup(str);

	while (str)
	{
		command = multi_command(&str, env);
		print_multi_command(command);
		printf("EXEC\n");
		clear_multi_command(command);
	}

	return (0);
}
