/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 16:52:37 by psemsari          #+#    #+#             */
/*   Updated: 2020/09/23 18:34:26 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int main(int argc, char **argv)
{
	char	*str;

	str = getcwd(NULL, PATH_MAX);
	(str == NULL) ? ft_putstr_fd(strerror(errno), 1) : write(1, str, ft_strlen(str));
	free(str);
	return (0);
}
