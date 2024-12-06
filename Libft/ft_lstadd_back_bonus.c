/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:50:35 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_elem;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_elem = ft_lstlast(*lst);
	last_elem->next = new;
}
