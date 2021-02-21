/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 02:10:41 by bemoreau          #+#    #+#             */
/*   Updated: 2021/02/21 14:37:50 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		scan_builtins(t_command *cmd, s_pipe *spipe)
{
	t_parser parse;

	parse = get_command(cmd->argument);
	if (ft_strncmp(parse.command, "cd", 3) == 0)
		return (0);
	if (ft_strncmp(parse.command, "unset", 6) == 0)
		return (0);
	if (ft_strncmp(parse.command, "env", 4) == 0)
		return (0);
	if (ft_strncmp(parse.command, "echo", 5) == 0)
		return (0);
	if (ft_strncmp(parse.command, "exit", 5) == 0)
		return (0);
	return (-1);
}

int		builtins(t_command *cmd, s_pipe *spipe)
{
	t_parser parse;

	parse = get_command(cmd->argument);
	if (ft_strncmp(parse.command, "cd", 3) == 0 && listlen(cmd) < 2)
		return (ft_cd(parse.argument));
	if (ft_strncmp(parse.command, "export", 7) == 0 && listlen(cmd) < 2)
		return (ft_export(parse.argument));
	if (ft_strncmp(parse.command, "unset", 6) == 0 && listlen(cmd) < 2)
		return (ft_unset(parse.argument));
	if (ft_strncmp(parse.command, "env", 4) == 0 && listlen(cmd) < 2)
		return (ft_env());
	if (ft_strncmp(parse.command, "echo", 5) == 0)
		return (ft_echo(parse.argument));
	if (ft_strncmp(parse.command, "exit", 5) == 0 && listlen(cmd) < 2)
		return (ft_exit(parse.argument, spipe));
	return (-1);
}
