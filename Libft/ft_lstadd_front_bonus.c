/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:31:29 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL || lst == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

/*int	main(void)
{
	t_list *l = ft_lstnew(ft_strdup("nyacat"));
    t_list *n = ft_lstnew(ft_strdup("OK"));
 
    ft_lstadd_front(&l, n);
    if (l == n && !strcmp(l->content, "OK"))
    {
        printf("YAAY\n");
    }
    printf("NOPE\n");
}*/