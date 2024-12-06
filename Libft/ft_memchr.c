/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:56:16 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*copy;
	unsigned char	a;

	copy = (unsigned char *) s;
	a = (unsigned char) c;
	while (n > 0)
	{
		if (*copy != a)
			copy++;
		else
			return ((void *) copy);
		n--;
	}
	return (NULL);
}

/*int main(void)
{
	char test[] = "cok\0kuk";
	printf("%s\n", memchr(test, 'u', 0));
	printf("%s\n", ft_memchr(test, 'u', 0));
}*/
