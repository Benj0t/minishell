/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 02:10:41 by bemoreau          #+#    #+#             */
/*   Updated: 2021/03/01 00:44:28 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_argsize(t_list *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		if (lst->content)
			i++;
		lst = lst->next;
	}
	return (i);
}

int		get_command(t_list *argument, t_parser *parse)
{
	int			len;
	int			i;

	len = ft_argsize(argument);
	if ((parse->argument = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
		return (-1);
	parse->argument[len] = NULL;
	i = 0;
	while (i < len)
	{
		if (argument->content)
		{
			parse->argument[i++] = argument->content;
		}
		argument = argument->next;
	}
	parse->command = parse->argument[0];
	return (0);
}

int		scan_builtins(t_command *cmd, t_pipe *spipe, t_parser *parse)
{
	int			ret;

	(void)cmd;
	(void)spipe;
	ret = 1;
	if (ft_strncmp(parse->command, "cd", 3) == 0)
		ret = 0;
	if (ft_strncmp(parse->command, "unset", 6) == 0)
		ret = 0;
	if (ft_strncmp(parse->command, "env", 4) == 0)
		ret = 0;
	if (ft_strncmp(parse->command, "echo", 5) == 0)
		ret = 0;
	if (ft_strncmp(parse->command, "exit", 5) == 0)
		ret = 0;
	if (ft_strncmp(parse->command, "export", 7) == 0)
		ret = 0;
	if (ft_strncmp(parse->command, "pwd", 4) == 0)
		ret = 0;
	return (ret);
}

int		builtins(t_command *cmd, t_pipe *spipe, t_parser *parse)
{
	int			ret;

	ret = 1;
	spipe->n_bin--;
	if (ft_strncmp(parse->command, "pwd", 4) == 0)
		ret = ft_pwd();
	if (ft_strncmp(parse->command, "cd", 3) == 0)
		ret = ft_cd(parse->argument);
	if (ft_strncmp(parse->command, "export", 7) == 0)
		ret = ft_export(parse->argument);
	if (ft_strncmp(parse->command, "unset", 6) == 0)
		ret = ft_unset(parse->argument);
	if (ft_strncmp(parse->command, "env", 4) == 0)
		ret = ft_env();
	if (ft_strncmp(parse->command, "echo", 5) == 0)
		ret = ft_echo(parse->argument);
	if (ft_strncmp(parse->command, "exit", 5) == 0)
		ret = ft_exit(parse->argument, spipe, cmd);
	return (ret);
}
