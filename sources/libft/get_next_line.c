/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:56:47 by psemsari          #+#    #+#             */
/*   Updated: 2020/02/17 16:40:46 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		mallocage(char **line, char *str)
{
	char *tmp;

	tmp = *line;
	*line = ft_strjoin(*line, str);
	free(tmp);
	if (*line == NULL)
		return (-1);
	return (0);
}

int		gnl_test(int check, char *str, char **line, int fd)
{
	if (mallocage(line, str) == -1)
		return (-1);
	ft_memset(str, 0, BUFFER_SIZE);
	check = read(fd, str, BUFFER_SIZE);
	str[check] = 0;
	return (gnl_rec(check, str, line, fd));
}

int		gnl_rec(int check, char *str, char **line, int fd)
{
	char *tmp;

	tmp = str;
	if (!check)
		return (mallocage(line, str) == -1 ? -1 : 0);
	if (*tmp)
	{
		while (*tmp && *tmp != '\n')
			tmp++;
		if (*tmp == '\n')
		{
			*tmp = 0;
			if (mallocage(line, str) == -1)
				return (-1);
			tmp++;
			while (*tmp)
				*str++ = *tmp++;
			*str = *tmp;
			return (1);
		}
	}
	if (!*tmp)
		return (gnl_test(check, str, line, fd));
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	str[(BUFFER_SIZE > 0 ? BUFFER_SIZE : 0) + 1];
	ssize_t		check;

	check = BUFFER_SIZE;
	if (line == NULL || read(fd, str, 0) || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_calloc(1, 1);
	return (gnl_rec(check, str, line, fd));
}
