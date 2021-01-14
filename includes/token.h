/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:28 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/14 13:31:05 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define T_ALL " 	\"'$;|><"
# define T_OPE "><|"
# define T_ENV "$"
# define T_QUO "'\""
# define T_END ";"
# define T_SEP " 	"
# define T_EOF '\0'
# define T_NOWORD 5

typedef enum	e_ttoken
{
	tok_word = 0,
	tok_space,
	tok_tab,
	tok_dblquote,
	tok_smpquote,
	tok_env,
	tok_end,
	tok_pipe,
	tok_out,
	tok_in,
	tok_eof,
	tok_outappend
}				t_ttoken;

typedef struct	s_token
{
	char		*name;
	t_ttoken	type;
}				t_token;

t_token		next_token(char **str);
int			parser_token(char **str, t_command *command);
t_token		view_next_token(const char *str);

#endif
