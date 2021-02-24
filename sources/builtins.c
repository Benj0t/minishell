/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 02:10:41 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/24 01:52:19 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_command(t_list *argument, t_parser *parse)
{
	int			len;
	int			i;

	len = ft_lstsize(argument);
	if ((parse->argument = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
		return (-1);
	parse->argument[len] = NULL;
	i = -1;
	while (++i < len)
	{
		parse->argument[i] = argument->content;
		argument = argument->next;
	}
	parse->command = parse->argument[0];
	return (0);
}

int		scan_builtins(t_command *cmd, s_pipe *spipe)
{
	t_parser parse;
	int ret;

	ret = 1;
	if ((get_command(cmd->argument, &parse)) == -1)
		return (-1);
	if (ft_strncmp(parse.command, "cd", 3) == 0)
		ret = 0;
	if (ft_strncmp(parse.command, "unset", 6) == 0)
		ret = 0;
	if (ft_strncmp(parse.command, "env", 4) == 0)
		ret = 0;
	if (ft_strncmp(parse.command, "echo", 5) == 0)
		ret = 0;
	if (ft_strncmp(parse.command, "exit", 5) == 0)
		ret = 0;
	if (ft_strncmp(parse.command, "export", 7) == 0)
		ret = 0;
	if (ft_strncmp(parse.command, "pwd", 4) == 0)
		ret = 0;
	free(parse.argument);
	return (ret);
}

int		builtins(t_command *cmd, s_pipe *spipe)
{
	t_parser parse;
	int ret;

	ret = 1;
	spipe->n_bin--;
	if ((get_command(cmd->argument, &parse)) == -1)
		return (-1);
	if (ft_strncmp(parse.command, "pwd", 4) == 0)
		ret = ft_pwd();
	if (ft_strncmp(parse.command, "cd", 3) == 0 && listlen(cmd) < 2)
		ret = ft_cd(parse.argument);
	if (ft_strncmp(parse.command, "export", 7) == 0)
		ret = ft_export(parse.argument);
	if (ft_strncmp(parse.command, "unset", 6) == 0 && listlen(cmd) < 2)
		ret = ft_unset(parse.argument);
	if (ft_strncmp(parse.command, "env", 4) == 0)
		ret = ft_env();
	if (ft_strncmp(parse.command, "echo", 5) == 0)
		ret = ft_echo(parse.argument);
	if (ft_strncmp(parse.command, "exit", 5) == 0 && listlen(cmd) < 2)
		ret = ft_exit(parse.argument, spipe, cmd);
	free(parse.argument);
	return (ret);
}
