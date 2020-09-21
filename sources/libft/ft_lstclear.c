/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:33:39 by psemsari          #+#    #+#             */
/*   Updated: 2019/10/24 12:50:54 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*base;

	if (!lst || !(*lst) || !del)
		return ;
	tmp = NULL;
	base = *lst;
	while (base)
	{
		tmp = base->next;
		ft_lstdelone(base, del);
		base = tmp;
	}
	*lst = NULL;
}
