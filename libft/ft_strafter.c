/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strafter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:05:38 by psemsari          #+#    #+#             */
/*   Updated: 2020/09/28 20:07:17 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strafter(char **str)
{
	size_t	i;
	size_t	ret;

	i = 0;
	while (str[0][i] != ' ' && str[0][i] != '	' && str[0][i] != '\0')
		i++;
	ret = i;
	while (str[0][i] == ' ' || str[0][i] == '	' || str[0][i] != '\0')
		i++;
	str = &str[i];
	return (ret);
}
