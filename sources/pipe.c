/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 16:30:54 by marvin            #+#    #+#             */
/*   Updated: 2021/02/19 19:08:29 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t child;

void	sig_quit(int sigid)
{
	if (sigid == SIGQUIT && child != 0)
	{
		write(1, "\n", 1);
		kill(child, SIGTERM);
	}
}

int		builtins(t_command *cmd, s_pipe *spipe)
{
	t_parser parse;

	parse = get_command(cmd->argument);
	if (ft_strncmp(parse.command, "cd", 3) == 0 && listlen(cmd) < 2)
		return (ft_cd(parse.argument));
	if (ft_strncmp(parse.command, "unset", 6) == 0)
		return (ft_unset(parse.argument));
	if (ft_strncmp(parse.command, "export", 7) == 0)
		return (ft_export(parse.argument));
	if (ft_strncmp(parse.command, "env", 4) == 0)
		return (list_env());
	if (ft_strncmp(parse.command, "echo", 5) == 0)
		return (ft_echo(parse.argument));
	if (ft_strncmp(parse.command, "exit", 5) == 0 && listlen(cmd) < 2)
		return (ft_exit(parse.argument));
	return (-1);
}

int		simple_command(t_command *cmd,\
						t_redir *redir, s_pipe *spipe)
{
	t_parser	comm1;
	int			ret;

	child = 0;
	comm1 = get_command(cmd->argument);
	set_local_env(spipe);
	exec_redir(cmd, redir);
	ret = builtins(cmd, spipe);
	if (ret == -1)
	{
		signal(SIGQUIT, &sig_quit);
		if ((child = fork()) == 0)
			execve(init_path(spipe->l_env, comm1, spipe),\
							comm1.argument, spipe->l_env);
		waitpid(child, (int *)&(spipe->pid[0]), 0);
		spipe->ret[0] = WEXITSTATUS(spipe->pid[0]);
	}
	end_redir(redir);
	return (ret);
}

int		ft_ret(int *ret)
{
	int i;

	i = 0;
	while (ret[i] != -1)
	{
		i++;
	}
	return ((unsigned char)ret[i - 1]);
}

int		execution(t_command *cmd, t_redir *redir, s_pipe *spipe)
{
	int i;

	i = 0;
	if (cmd->argument == NULL)
		return (-1);
	spipe->n_comm = listlen(cmd);
	spipe->i_comm = 0;
	spipe->i_pipe = 0;
	spipe->n_pipe = spipe->n_comm - 1;
	if (!init_spipe(spipe))
		return (-1);
	if (spipe->n_comm == 1)
		simple_command(cmd, redir, spipe);
	else if (spipe->n_comm == 2)
	{
		single_pipe(cmd, redir, spipe);
	}
	else if (spipe->n_comm > 2)
	{
		multi_pipe(cmd, spipe, redir);
	}
	spipe->last_ret = spipe->ret[spipe->n_comm - 1];
	free_spipe(spipe);
	return (1);
}
