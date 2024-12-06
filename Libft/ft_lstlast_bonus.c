/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:27:59 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

/*int	main(void)
{
		t_list *l;
        t_list *expected;
        t_list *actual;
 
        l = ft_lstnew(ft_strdup("1"));
        l->next = ft_lstnew(ft_strdup("2"));
        l->next->next = ft_lstnew(ft_strdup("3"));
        expected = l->next->next;
        actual = ft_lstlast(l);
		printf("%s\n", expected->content);
		printf("%s\n", actual->content);
        if (actual == expected)
                printf("YAAY\n");
        printf("NOPE\n");
}*/
