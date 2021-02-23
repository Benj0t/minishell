/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:19:52 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/23 14:28:13 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define T_ALL " 	><;|"
# define T_EOF '\0'
# define T_NOWORD 4

# define EUNEXPECTED "syntax error near unexpected token"

typedef struct	s_managparse
{
	t_command	*command;
	t_redir		redir;
	s_pipe		spipe;
	char		*str;
}				t_managparse;

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

char			in_list(char c, char *str);
t_ttoken		search_type(char c);
int				is_quote(char c);
int				backslash(char *str, size_t i);
int				is_backslash(char *str, size_t i);
t_token			word_tok(t_managparse *manag, size_t i);
t_token			others_tok(t_managparse *manag);
t_token			error_quote(t_managparse *manag, char quote);
size_t			quote_pass(t_managparse *manag, size_t i, char quote);
t_token			next_token(t_managparse *manag);
char			*env_dbl_join(char **str, char *var, size_t ret);
char			*env_sub_var(t_managparse *manag, char *tmp);
size_t			env_sub(char **str, t_managparse *manag, size_t i);
size_t			env_token(char **str, t_managparse *manag, size_t i);

char			*join_name(t_token *tok, t_managparse *manag, char *result);
char			*dup_name(t_token *tok, t_managparse *manag,\
							char *result, size_t i);
char			*dbl_join(t_token *tok, t_managparse *manag,\
							char *var, size_t ret);
char			*var_to_replace(t_token *tok, t_managparse *manag, char *tmp);
size_t			ft_subvar(t_token *tok, t_managparse *manag, size_t i);
int				environnment_expander(t_token *tok, t_managparse *manag);
int				remove_char(char **s, size_t here);
char			*quote_exp(t_token *tok, t_managparse *manag,\
							char *result, size_t *i);
int				expansion(t_token *tok, t_managparse *manag);
int				backslash_remove(t_token *tok, t_managparse *manag);
int				backslash_lvl(char *str, size_t i);
void			backslash_quote(t_token *tok, size_t *i, char quote);

void			malloc_fail(t_token tok, t_managparse *manag);
int				error_parser(char *str, char *name);
int				save_arg(t_token *tok, t_managparse *manag, t_list **list);
int				test_arg(t_token *tok, t_managparse *manag, t_list **list);
void			next_free_token(t_token *tok, t_managparse *manag);
int				save_tok_out(t_token *tok, t_managparse *manag);
int				save_tok_in(t_token *tok, t_managparse *manag);
int				save_tok_pipe(t_token *tok, t_managparse *manag);
int				parser_token(t_managparse *manag);

void			clear_multi_command(t_command *command);
void			print_multi_command(t_command *command);
t_command		*setup_command(void);
int				parser(char **str, t_redir *redir, s_pipe *spipe);

#endif
