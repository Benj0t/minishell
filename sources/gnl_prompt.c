/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:56:47 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/28 14:36:57 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				g_signal_c;
int				g_signal_b;
extern int		g_child;

void	sig_handler(int sigid)
{
	g_signal_c = 1;
	if (sigid == SIGINT && g_child != 0)
	{
		ft_putchar_fd('\n', 2);
		kill(g_child, SIGINT);
		g_child = 0;
	}
	else if (sigid == SIGINT)
	{
		ft_putstr_fd("\n> ", 2);
	}
	return ;
}

void	ign_sig(int sigid)
{
	g_signal_b = 131;
	if (sigid == SIGQUIT && g_child != 0)
	{
		kill(g_child, SIGQUIT);
		g_child = 0;
	}
	return ;
}

int		prompt_test(int check, char *str, char **line, int *last_ret)
{
	if (prompt_malloc(line, str) == -1)
		return (-1);
	ft_memset(str, 0, BUFFER_SIZE);
	check = read(0, str, BUFFER_SIZE);
	if (g_signal_c == 1)
	{
		*last_ret = 130;
		if (*line)
			free(*line);
		*line = ft_calloc(1, 1);
		g_signal_c = 0;
	}
	if (check == 0)
	{
		write(2, "exit\n", 5);
		free(*line);
		ft_lstclear(&g_env, &dealloc_varenv);
		exit(*last_ret);
	}
	str[check] = 0;
	return (prompt_rec(check, str, line, last_ret));
}

int		prompt_rec(int check, char *str, char **line, int *last_ret)
{
	char *tmp;

	tmp = str;
	if (!check)
		return (prompt_malloc(line, str) == -1 ? -1 : 0);
	if (*tmp)
	{
		while (*tmp && *tmp != '\n')
			tmp++;
		if (*tmp == '\n')
		{
			*tmp = 0;
			if (prompt_malloc(line, str) == -1)
				return (-1);
			tmp++;
			while (*tmp)
				*str++ = *tmp++;
			*str = *tmp;
			return (1);
		}
	}
	if (!*tmp)
		return (prompt_test(check, str, line, last_ret));
	return (1);
}

int		gnl_prompt(int fd, char **line, int *last_ret)
{
	static char	str[(BUFFER_SIZE > 0 ? BUFFER_SIZE : 0) + 1];
	ssize_t		check;

	check = BUFFER_SIZE;
	g_signal_b = 0;
	g_signal_c = 0;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &ign_sig);
	if (line == NULL || read(fd, str, 0) || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_calloc(1, 1);
	return (prompt_rec(check, str, line, last_ret));
}
