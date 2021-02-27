/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:37:51 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/27 16:29:52 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstrm(t_list **lst)
{
	t_list	*tmp;
	t_list	*base;

	if (!lst || !(*lst))
		return ;
	tmp = NULL;
	base = *lst;
	while (base)
	{
		tmp = base->next;
		free(base);
		base = tmp;
	}
	*lst = NULL;
}

t_list		*ft_lstcopy(t_list *list)
{
	t_list	*tmp;
	t_list	*ret;
	t_list	*tmp2;

	tmp = list;
	ret = NULL;
	while (tmp != NULL)
	{
		if (ret == NULL)
		{
			ret = ft_lstnew(tmp->content);
			if (ret == NULL)
				return (NULL);
		}
		else
		{
			tmp2 = ft_lstnew(tmp->content);
			if (tmp2 == NULL)
			{
				ft_lstrm(&ret);
				return (NULL);
			}
			ft_lstadd_back(&ret, tmp2);
		}
		tmp = tmp->next;
	}
	return (ret);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		ret;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if ((unsigned char)s1[i] - (unsigned char)s2[i] > 0)
		ret = 1;
	else if ((unsigned char)s1[i] - (unsigned char)s2[i] < 0)
		ret = -1;
	else
		ret = 0;
	return (ret);
}

void		swap(t_list *a, t_list *b)
{
	void *temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void		bubble_sort(t_list *list)
{
	int		swapped;
	t_list	*ptr;
	t_list	*last_ptr;

	last_ptr = NULL;
	if (list == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = list;
		while (ptr->next != last_ptr)
		{
			if (ft_strcmp(((t_var_env *)ptr->content)->key,\
				((t_var_env *)ptr->next->content)->key))
			{
				swap(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
		last_ptr = ptr;
	}
}
