/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:46:28 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/26 15:54:03 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define T_ALL " 	\\;|><"
# define T_EOF '\0'
# define T_NOWORD 6

# define EUNEXPECTED "syntax error near unexpected token"

typedef enum	e_ttoken
{
	tok_word = 0,
	tok_space,
	tok_tab,
	tok_backslash,
	tok_end,
	tok_pipe,
	tok_out,
	tok_in,
	tok_eof,
	tok_error
}				t_ttoken;

typedef struct	s_token
{
	char		*name;
	t_ttoken	type;
}				t_token;

t_token		next_token(char **str);
t_token		view_next_token(const char *str);
int			is_quote(char c);
void		smplquote_expander(char **result, t_token *tok);
void		environnment_expander(char **str, t_token *tok, t_list *env, s_pipe *spipe);
void		dblquote_expander(char **result, t_token *tok, t_list *env, s_pipe *spipe);
void		backslash(char **str, t_token *tok);
void		expansion(t_token *tok, t_list *env, s_pipe *spipe);

#endif
