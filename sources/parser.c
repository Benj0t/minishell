/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_old.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:16:26 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/11 13:38:44 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_symbol(char *str) //get token type
{
	char	*symbols[8] = {">>", ">", "<", "|", "$", ";", "'", "\""};
	int		i;

	i = 0;
	while (i < 8)
	{
		if (!ft_strncmp(str, symbols[i], ft_strlen(symbols[i])))
			return (symbols[i]);
		i++;
	}
	return (NULL);
}

//remplace search par replace dans un str
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

//systeme pour les exceptions d'arg ($, double et simple quotes)
char	*arg_except(char **str, char *ret, t_list *env) //parser (path to go)
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

//renvoie la prochaine chaine
char	*arg_next(char **str) //token next
{
	size_t	i;
	size_t	i2;
	char	*ret;
	char	*tmp;
	char	*symbol;

	i = 0;
	symbol = NULL;
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
	symbol = check_symbol(&str[0][i]);
	while (symbol == NULL && str[0][i] != ' ' && str[0][i] != '	' && str[0][i] != '\0')
	{
		i++;
		symbol = check_symbol(&str[0][i]);
	}
	if (symbol != NULL && i == 0)
	{
		ret = (char *)malloc(ft_strlen(symbol) + 1);
		ft_strlcpy(ret, *str, ft_strlen(symbol) + 1);
		tmp = ft_strdup(&str[0][ft_strlen(symbol)]);
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

//renvoie un next argument qui a un $ devant
char	*arg_env(char **str, char *ret, t_list *lst_env, s_pipe *spipe)
{
	char	*search;
	char	*result;
	//voir $?
	search = arg_next(str);
	free(ret);
	if (!ft_strncmp(search, "?", 1))
		return (ft_strdup(ft_itoa(ft_ret(spipe->ret)))); //à voir
	result = get_env_var(search, lst_env);
	free(search);
	if (result == NULL)
		return (NULL);
	return (ft_strdup(result));
}

char	*next(char **str, t_list *env, s_pipe *spipe)
{
	char		*ret;

	if (*str == NULL)
		return (NULL);
	if ((ret = arg_next(str)) != NULL)
	{
		if (ret[0] == '\"' || ret[0] == '\'')
			ret = arg_except(str, ret, env);
		else if (ret[0] == '$')
			ret = arg_env(str, ret, env, spipe);
	}
	return (ret);
}

//setup t_command
void	setup_command(t_command *ret)
{
	ret->argument = NULL;
	ret->redir_in = NULL;
	ret->redir_out = NULL;
	ret->redir_append = NULL;
	ret->pipe = NULL;
}

//enregistre plusieur t_command (recursif)
t_command	*multi_command(char **str, t_list *env, s_pipe *spipe)
{
	t_command	*command;
	char		*ret;

	command = malloc(sizeof(t_command));
	setup_command(command);
	command->pipe = NULL;
	command->argument = NULL;
	command->redir_in = NULL;
	command->redir_out = NULL;
	command->redir_append = NULL;
	ret = next(str, env, spipe);
	while (ret != NULL)
	{
		if (!ft_strncmp(ret, ">>", 2))
		{
			free(ret);
			ret = next(str, env, spipe);
			ft_lstadd_back(&command->redir_append, ft_lstnew(ret));
		}
		else if (!ft_strncmp(ret, ">", ft_strlen(ret)))
		{
			free(ret);
			ret = next(str, env, spipe);
			ft_lstadd_back(&command->redir_out, ft_lstnew(ret));
		}
		else if (!ft_strncmp(ret, "<", ft_strlen(ret)))
		{
			free(ret);
			ret = next(str, env, spipe);
			ft_lstadd_back(&command->redir_in, ft_lstnew(ret));
		}
		else if (!ft_strncmp(ret, "|", ft_strlen(ret)))
		{
			free(ret);
			command->pipe = multi_command(str, env, spipe);
		}
		else if (!ft_strncmp(ret, ";", ft_strlen(ret)))
		{
			free(ret);
			return (command);
		}
		else
			ft_lstadd_back(&command->argument, ft_lstnew(ret));
		ret = next(str, env, spipe);
	}
	free(ret);
	return (command);
}

//desalloc et clear t_command
void		clear_multi_command(t_command *command)
{
	t_command	*tmp;

	tmp = NULL;
	while (command != NULL)
	{
		tmp = command->pipe;
		ft_lstclear(&command->argument, free);
		ft_lstclear(&command->redir_in, free);
		ft_lstclear(&command->redir_append, free);
		ft_lstclear(&command->redir_out, free);
		free(command);
		command = tmp;
	}
}

//print t_command
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
		while (command->redir_append != NULL)
		{
			printf("	redir_append: -%s-\n", (char *)command->redir_append->content);
			command->redir_append = command->redir_append->next;
		}
		command = command->pipe;
	}
}

//start du parser
int		parser(char *str, t_list *env, t_redir *redir, s_pipe *spipe)
{
	t_command	*command;
	t_list		*arg;

	str = ft_strdup(str);
	while (str)
	{
		command = multi_command(&str, env, spipe);
		//print_multi_command(command);
		//printf("EXEC\n");
		execution(env, command, redir, spipe);
		clear_multi_command(command);
	}

	return (0);
}
