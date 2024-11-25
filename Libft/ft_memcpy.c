/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:54:11 by gdero             #+#    #+#             */
/*   Updated: 2023/10/17 16:23:08 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	while (n != 0)
	{
		d[i] = s[i];
		i++;
		n--;
	}
	return ((void *) d);
}

/*int	main(void)
{
	char	*test = "coucou les gens ca va bien";
	char	*test2 = "coucou les gens ca va bien";
	char	*src = "Hello comment ca va";
	test = malloc(28);
	test2 = malloc(28);
	memcpy(test, src, 16);
	ft_memcpy(test2, src, 16);
	printf("%s\n", test);
	printf("%s\n", test2);
	free(test);
	free(test2);
}*/
