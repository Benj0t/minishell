/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:19:52 by psemsari          #+#    #+#             */
/*   Updated: 2021/01/19 09:25:23 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "pipe.h"

t_parser get_command(t_list *argument);

t_command	*setup_command(void);
int			parser_token(char **str, t_command *command, t_list *env, s_pipe *spipe);

#endif
