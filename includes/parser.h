/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:19:52 by psemsari          #+#    #+#             */
/*   Updated: 2020/11/19 15:07:44 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct	s_var_env
{
	char	*key;
	char	*var;
}				t_var_env;

size_t			next_space(char *str);
int				parser(char *str, t_list *env);

typedef struct	s_parser
{
		char	*command;
		char	**argument;
}				t_parser;

t_parser get_command(char const *str);

#endif
