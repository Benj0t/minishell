/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:24:01 by psemsari          #+#    #+#             */
/*   Updated: 2020/09/21 15:02:38 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	pid_t		child;
	char		*str;
	t_parser	parse;
	int			ret;

	while (1)
	{
		ft_putnstr("minishell> ", 12);
		get_next_line(0, &str);
		parse.argument = ft_split(str, ' ');
		parse.command = ft_strjoin("/bin/", parse.argument[0]);
		child = fork();
		if (child == 0)
			printf("%d %s\n", execve(parse.command, parse.argument, envp), strerror(errno));
		else
			waitpid(child, &ret, WUNTRACED);
	}
	return (0);
}

