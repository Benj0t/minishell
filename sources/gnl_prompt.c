/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:56:47 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/21 14:04:35 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_c;

void	sig_handler(int sigid)
{
	if (sigid == SIGINT)
	{
		g_signal_c = 1;
		ft_putstr_fd("\n> ", 2);
	}
	return ;
}

void	ign_sig(int sigid)
{
	return;
}

int		prompt_malloc(char **line, char *str)
{
	char *tmp;

	tmp = *line;
	*line = ft_strjoin(*line, str);
	free(tmp);
	if (*line == NULL)
		return (-1);
	return (0);
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
	if ((check == 0) && (ft_strlen(*line) == 0))
	{
		*last_ret = 130;
		write(2, "exit\n", 5);
		free(*line);
		ft_lstclear(&g_env, free);
		exit(9);
	}
	if (check == 0)
		check = 1;
	str[check] = 0;
	return (prompt_rec(check, str, line, 0));
}

int		prompt_rec(int check, char *str, char **line, int *last_ret)
{
	char *tmp;

	tmp = str;
	if (!check && *line[ft_strlen(*line) - 1] != -1)
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
	char		str[(BUFFER_SIZE > 0 ? BUFFER_SIZE : 0) + 1];
	ssize_t		check;

	check = BUFFER_SIZE;
	g_signal_c = 0;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &ign_sig);
	if (line == NULL || read(fd, str, 0) || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_calloc(1, 1);
	return (prompt_rec(check, str, line, last_ret));
}
