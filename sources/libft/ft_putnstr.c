/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:10:27 by psemsari          #+#    #+#             */
/*   Updated: 2019/11/19 15:32:13 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr(char *s, size_t n)
{
	size_t len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(1, s, (n > len ? len : n));
}
