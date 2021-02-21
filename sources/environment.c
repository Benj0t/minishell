/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:40:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/21 19:37:35 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_env(char *s)
{
	size_t i;

	i = 0;
	if (ft_isdigit(s[i]) || s[i] == '?')
		return (1);
	while (s[i])
	{
			if (!ft_isalnum(s[i]) && s[i] != '_')
			{
				if (i == 0)
					return (0);
				else
					break;
			}
		i++;
	}
	return (i);
}

int			valid_env(char *s)
{
	size_t i;

	i = 0;
	if (s[i] == '=' || ft_isdigit(s[i]))
		return (0);
	while (s[i] && s[i] != '=' && s[i] != '+')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (i);
}

void		print_env(char	*prefix, t_list *env, int print_null)
{
	t_var_env	*var_env;
	t_list		*tmp_env;

	tmp_env = env;
	while (tmp_env != NULL)
	{
		var_env = (t_var_env *)tmp_env->content;
		if (var_env->var)
			printf("%s%s=%s\n", prefix, var_env->key, var_env->var);
		else if (!var_env->var && print_null)
			printf("%s%s\n", prefix, var_env->key);
		tmp_env = tmp_env->next;
	}
}

t_var_env	*malloc_varenv(const char *key, const char *str)
{
	t_var_env	*ret;

	ret = (t_var_env *)malloc(sizeof(t_var_env));
	ret->var = NULL;
	ret->key = ft_strdup(key);
	if (str != NULL)
		ret->var = ft_strdup(str);
	return (ret);
}

void		dealloc_varenv(t_var_env *var_env)
{
	free(var_env->key);
	if (var_env->var != NULL)
		free(var_env->var);
	free(var_env);
}

t_list	*envp_to_list(char **envp)
{
	int		i;
	char	*c;
	t_list	*ret;

	ret = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		c = ft_strchr(envp[i], '=');
		c[0] = '\0';
		if (i == 0)
			ret = ft_lstnew(malloc_varenv(envp[i], &c[1])); //malloc
		else
			ft_lstadd_back(&ret, ft_lstnew(malloc_varenv(envp[i], &c[1]))); //malloc
		i++;
	}
	return (ret);
}

char	**list_to_envp(void)
{
	int		len;
	int		i;
	char	**ret;
	t_list	*tmp;

	tmp = g_env;
	len = ft_lstsize(tmp);
	ret = (char **)malloc(sizeof(char *) * (len + 1)); //malloc
	i = 0;
	while (tmp != NULL)
	{
		ret[i] = ft_strjoin_c(((t_var_env *)tmp->content)->key,
					((t_var_env *)tmp->content)->var, '='); //malloc
		tmp = tmp->next;
		i++;
	}
	ret[len] = NULL;
	return (ret);
}

void	dealloc_tab(char **tab)
{
	char	**start;

	start = tab;
	while (*tab != NULL)
	{
		free(*tab);
		tab++;
	}
	free(start);
}

char	*get_env(const char *name)
{
	t_list		*tmp_env;

	if (name == NULL)
		return (NULL);
	tmp_env = g_env;
	while (tmp_env != NULL)
	{
		if (!strcmp(((t_var_env *)tmp_env->content)->key, name)) //changer strcmp
			return (((t_var_env *)tmp_env->content)->var);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

t_var_env	*getvar_env(const char *name)
{
	t_list		*tmp_env;

	tmp_env = g_env;
	while (tmp_env != NULL)
	{
		if (!strcmp(((t_var_env *)tmp_env->content)->key, name)) //changer strcmp
			return ((t_var_env *)tmp_env->content);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

int		join_env(const char *name, char *value)
{//voir si key est valable et voir += et env de depart
	t_var_env	*tmp;
	char		*str;

	tmp = getvar_env(name);
	if (tmp)
	{
		str = tmp->var;
		if (!str)
			tmp->var = ft_strdup(value);
		else
			tmp->var = ft_strjoin(tmp->var, value);
		if (tmp->var == NULL)
			return (-1);
		if (str != NULL)
			free(str);
	}
	else if (!tmp)
		ft_lstadd_back(&g_env, ft_lstnew(malloc_varenv(name, value)));
	return (0);
}

int		put_env(char *string)
{
	size_t i;

	i = is_valid_env(string);
	if (string[i] == '\0')
		return(set_env(string, NULL, 0));
	string[i] = '\0';
	if (string[i - 1] == '+')
	{
		string[i - 1] = '\0';
		return (join_env(string, &string[i + 1]));
	}
	return (set_env(string, &string[i + 1], 1));
}

int		set_env(const char *name, char *value, int replace)
{//voir si key est valable et voir += et env de depart
	t_var_env *tmp;

	tmp = getvar_env(name);
	if (replace && tmp)
	{
		free(tmp->var);
		tmp->var = ft_strdup(value);
		if (tmp->var == NULL)
			return (-1);
	}
	else if (!tmp)
		ft_lstadd_back(&g_env, ft_lstnew(malloc_varenv(name, value)));
	return (0);
}

int		contains_egal(const char *name)
{
	size_t i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		unset_env(const char *name)
{
	t_list		*tmp_env;
	t_list		*tmp;

	if (name == NULL || ft_strlen(name) == 0 || contains_egal(name))
		return (-1);
	tmp_env = g_env;
	while (tmp_env != NULL)
	{
		if (!strcmp(((t_var_env *)tmp_env->content)->key, name)) //changer strcmp
		{
			tmp->next = tmp_env->next;
			dealloc_varenv((t_var_env *)tmp_env->content);
		}
		tmp = tmp_env;
		tmp_env = tmp_env->next;
	}
	return (0);
}
