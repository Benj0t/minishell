/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:59:14 by psemsari          #+#    #+#             */
/*   Updated: 2019/10/26 15:04:17 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_tabfree(char **tab)
{
	size_t a;

	a = 0;
	while (tab[a])
	{
		free(tab[a]);
		a++;
	}
	return (0);
}

static int		ft_mallocage(char const *str, char **tab, char c)
{
	size_t	i;
	size_t	a;
	size_t	count;

	a = 0;
	i = 0;
	while (str[i] != '\0')
	{
		count = 0;
		while (str[i] == c)
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] != c && str[i] != '\0')
		{
			i++;
			count++;
		}
		if (!(tab[a] = ft_calloc(count + 1, sizeof(char))))
			return (ft_tabfree(tab));
		a++;
	}
	return (1);
}

static void		ft_filltab(char const *str, char **tab, char c)
{
	size_t	i;
	size_t	a;
	size_t	count;

	a = 0;
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		while (str[i] != c && str[i] != '\0')
		{
			tab[a][count] = str[i];
			count++;
			i++;
		}
		if (count > 0)
			tab[a][count] = '\0';
		else
			tab[a] = 0;
		a++;
		count = 0;
	}
}

static size_t	ft_test(char const *s, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			len++;
		i++;
	}
	return (len);
}

char			**ft_split(char const *s, char c)
{
	size_t	len;
	char	**tab;

	if (!s)
		return (NULL);
	if (ft_strlen(s) == 0)
	{
		if (!(tab = ft_calloc(1, sizeof(tab))))
			return (NULL);
		tab[0] = 0;
		return (tab);
	}
	len = ft_test(s, c);
	if (!(tab = ft_calloc(len + 1, sizeof(tab))))
		return (NULL);
	tab[len] = NULL;
	if (!(ft_mallocage(s, tab, c)))
	{
		free(tab);
		return (NULL);
	}
	ft_filltab(s, tab, c);
	return (tab);
}
