/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:03:02 by gdero             #+#    #+#             */
/*   Updated: 2023/10/16 17:56:37 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*b, int c, size_t len)
{
	unsigned long		i;
	unsigned char		*test;

	i = 0;
	test = (unsigned char *) b;
	while (i < len)
	{
		test[i] = c;
		i++;
	}
	return ((void *) test);
}

/*int main(void)
{
	char test2[] = "coucou les gens";
	char test[] = "coucou les gens";
	memset(test, 94, 4);
	ft_memset(test2, 94, 4);
	printf("%s\n", test);
	printf("%s\n", test2);
}*/
