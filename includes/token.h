/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:28 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/17 10:19:08 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define T_ALL " 	><;|"
# define T_EOF '\0'
# define T_NOWORD 4

# define EUNEXPECTED "syntax error near unexpected token"

typedef enum	e_ttoken
{
	tok_word,
	tok_space,
	tok_tab,
	tok_out,
	tok_in,
	tok_end,
	tok_pipe,
	tok_eof,
	tok_error,
	tok_null
}				t_ttoken;

typedef struct	s_token
{
	char		*name;
	t_ttoken	type;
}				t_token;

t_token		next_token(t_managparse *manag);
int			is_quote(char c);
int			environnment_expander(t_token *tok, t_managparse *manag);
int			backslash(char *str, size_t i);
int			expansion(t_token *tok, t_managparse *manag);
int			backslash_remove(t_token *tok, t_managparse *manag);
void		malloc_fail(t_token tok, t_managparse *manag);

#endif
