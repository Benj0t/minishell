/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:56:02 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/23 17:27:45 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

int			get_command(t_list *argument, t_parser *parse);
int			get_path_id(char **env);
char		*ft_path(char **env, t_parser comm);

#endif
