/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:35:44 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/*int	main(void)
{
	char c;
	t_list *elem;
	elem = malloc(2 * sizeof(t_list));
	t_list *elem2;
	elem2 = malloc(2 *sizeof(t_list));
	t_list *elem3;
	elem3 = malloc(2 *sizeof(t_list));
	t_list *elem4;
	elem4 = malloc(2*sizeof(t_list));
	elem->next = elem2;
	elem2->next = elem3;
	elem3->next = elem4;
	c = ft_lstsize(elem) + 48;
	write(1, &c, 1);
	write(1, "\n", 1);
	elem->next = NULL;
	c = ft_lstsize(elem) + 48;
	write(1, &c, 1);
	write(1, "\n", 1);
	elem = NULL;
	c = ft_lstsize(elem) + 48;
	write(1, &c, 1);
	write(1, "\n", 1);
	free(elem);
	free(elem2);
	free(elem3);
	free(elem4);
}*/