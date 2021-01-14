/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:19:52 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/14 15:58:05 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "pipe.h"

size_t			next_space(char *str);

typedef struct	s_command
{
		t_list				*argument;
		t_list				*redir_append;
		t_list				*redir_out;
		t_list				*redir_in;
		struct s_command	*pipe;
}				t_command;

typedef struct	s_var_env
{
	char	*key;
	char	*var;
}				t_var_env;

typedef struct	s_parser
{
		char	*command;
		char	**argument;
}				t_parser;

t_parser get_command(t_list *argument);

t_command	*setup_command(void);

#endif
