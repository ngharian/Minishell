/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:49:13 by gdero             #+#    #+#             */
/*   Updated: 2023/10/17 16:15:04 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long	i;
	unsigned char	*string1;
	unsigned char	*string2;

	i = 0;
	string1 = (unsigned char *) s1;
	string2 = (unsigned char *) s2;
	while (i < n)
	{
		if (string1[i] == '\0' && string2[i] == '\0')
			return (0);
		if (string1[i] != string2[i])
			return (string1[i] - string2[i]);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	const char test[] = "\200";
	const char test2[] = "\0";
	printf("%i\n", strncmp(test, test2, 5));
	printf("%i\n", ft_strncmp(test, test2,5));
}*/
