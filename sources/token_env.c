/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:44:00 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/24 14:53:30 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*env_dbl_join(char **str, char *var, size_t ret)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(*str, var);
	if (tmp == NULL)
		return (NULL);
	tmp2 = ft_strjoin(tmp, &str[0][ret]);
	free(tmp);
	if (tmp2 == NULL)
		return (NULL);
	free(*str);
	return (tmp2);
}

char		*env_sub_var(t_managparse *manag, char *tmp)
{
	char	*var;

	if (tmp[0] == '?')
		var = ft_itoa(manag->spipe->last_ret);
	else
	{
		var = get_env(tmp);
		if (var == NULL)
			var = ft_strdup("");
		else
			var = ft_strdup(get_env(tmp));
	}
	return (var);
}

size_t		env_sub(char **str, t_managparse *manag, size_t i)
{
	size_t	ret;
	char	*tmp;
	char	*tmp2;
	char	*var;

	str[0][i] = '\0';
	ret = 1;
	while (str[0][i + 1 + ret] && str[0][i + 1] != '?' \
		&& !ft_isdigit(str[0][i + 1]))
	{
		if (!ft_isalnum(str[0][i + 1 + ret]) \
			&& str[0][i + 1 + ret] != '_')
			break ;
		ret++;
	}
	tmp = ft_substr(&str[0][i + 1], 0, ret);
	if (tmp == NULL)
		return (i);
	var = env_sub_var(manag, tmp);
	free(tmp);
	if (var == NULL)
		return (i);
	ret = i + 1 + ret;
	*str = env_dbl_join(str, var, ret);
	free(var);
	return (i);
}

size_t		env_token(char **str, t_managparse *manag, size_t i)
{
	int		bshlvl;
	int		remove;

	if (str[0][i] == '$')
	{
		bshlvl = backslash_lvl(str[0], i);
		if ((bshlvl % 2) == 0)
		{
			i = env_sub(str, manag, i);
			return (i);
		}
	}
	return (i + 1);
}
