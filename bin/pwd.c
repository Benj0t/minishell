/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 16:52:37 by psemsari          #+#    #+#             */
/*   Updated: 2020/09/22 17:04:47 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int main(int argc, char **argv)
{
	char	str[1000];

	getcwd(str, 1000);
	write(0, str, ft_strlen(str));
	return (0);
}