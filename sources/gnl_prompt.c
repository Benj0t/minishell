/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:56:47 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/12 15:40:52 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		prompt_test(int check, char *str, char **line, int fd)
{
	if (prompt_malloc(line, str) == -1)
		return (-1);
	ft_memset(str, 0, BUFFER_SIZE);
	check = read(fd, str, BUFFER_SIZE);
	if ((check == 0) && (ft_strlen(*line) == 0))
	{
		write(1, "exit\n", 5);
		free(*line);
		exit(9);
	}
	if (check == 0)
		check = 1;
	str[check] = 0;
	return (prompt_rec(check, str, line, fd));
}

int		prompt_rec(int check, char *str, char **line, int fd)
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
		return (prompt_test(check, str, line, fd));
	return (1);
}

int			gnl_prompt(int fd, char **line)
{
	char	str[(BUFFER_SIZE > 0 ? BUFFER_SIZE : 0) + 1];
	ssize_t		check;

	check = BUFFER_SIZE;
	if (line == NULL || read(fd, str, 0) || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_calloc(1, 1);
	return (prompt_rec(check, str, line, fd));
}
