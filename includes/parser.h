/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:19:52 by psemsari          #+#    #+#             */
/*   Updated: 2020/12/08 15:16:58 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

size_t			next_space(char *str);
int				parser(char *str, t_list *env);

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

#endif
