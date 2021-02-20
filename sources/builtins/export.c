/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:34:02 by psemsari          #+#    #+#             */
/*   Updated: 2021/02/20 18:42:03 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(char **arg)
{
	t_list *copy;

	arg++;
	if (*arg == NULL)
	{
		copy = ft_lstcopy(g_env);
		bubble_sort(copy);
		print_env("export", copy);
		ft_lstclear(&copy, NULL);
		return (0);
	}
	while (*arg != NULL)
	{
		if (put_env(*arg))
			return (1);
		arg++;
	}
	return (0);
}
