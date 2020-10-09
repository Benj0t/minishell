/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:19:52 by psemsari          #+#    #+#             */
/*   Updated: 2020/10/09 17:18:34 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct	s_command
{
		t_list				*argument;
		t_list				*redir_out;
		t_list				*redir_in;
		struct s_command	*pipe;
}				t_command;

typedef struct	s_var_env
{
	char	*key;
	char	*var;
}				t_var_env;

size_t			next_space(char *str);
int				parser(char *str, t_list *env);

#endif
