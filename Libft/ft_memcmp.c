/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student,s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:23:44 by gdero             #+#    #+#             */
/*   Updated: 2023/10/17 16:29:13 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;

	string1 = (unsigned char *) s1;
	string2 = (unsigned char *) s2;
	while (n != 0)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
		n--;
	}
	return (0);
}

/*int	main(void)
{
	char test[] = "";
	char test2[] = "";
	printf("%i\n", memcmp(test, test2, 2));
	printf("%i\n", ft_memcmp(test, test2, 2));
}*/
