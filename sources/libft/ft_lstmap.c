/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:44:04 by psemsari          #+#    #+#             */
/*   Updated: 2019/10/24 13:00:59 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *res;
	t_list *first;

	if (!lst || !f || !del)
		return (NULL);
	if (!(res = ft_lstnew(f(lst->content))))
		return (NULL);
	first = res;
	lst = lst->next;
	while (lst)
	{
		res->next = ft_lstnew(f(lst->content));
		if (!res->next)
		{
			ft_lstclear(&res, del);
			return (res);
		}
		res = res->next;
		lst = lst->next;
	}
	res->next = NULL;
	return (first);
}
