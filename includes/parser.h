/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:19:52 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/17 10:19:56 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "pipe.h"

t_parser get_command(t_list *argument);

t_command	*setup_command(void);
int			parser_token(t_managparse *manag);

#endif
