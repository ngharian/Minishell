/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:01:24 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (dstsize < 1)
		return (j);
	if (src[0] == '\0')
	{
		dst[0] = '\0';
		return (j);
	}
	while (dstsize > 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
		dstsize--;
	}
	dst[i] = '\0';
	return (j);
}

/*int	main(void)
{
	char *dest = NULL;
	char *dest2 = NULL;
	char src[] = "Coucou ca va";
	//printf("%lu %lu\n", strlcpy(dest, src, 2), ft_strlcpy(dest2, src, 2));
	printf("%lu\n", strlcpy(dest, src, 1));
	//printf("%lu\n", ft_strlcpy(dest2, src, 1));
	//ft_strlcpy(dest2, src, 2);
	//printf("%s\n", dest);
	//printf("%s\n", dest2);
}*/

/*int main(void)
{
	char *dest;
	char *dest2;
	dest = (char *)malloc(sizeof(*dest) * 15);
	dest2 = (char *)malloc(sizeof(*dest2) * 15);
	memset(dest, 0, 15);
	memset(dest, 'r', 6);
	memset(dest2, 0, 15);
	memset(dest2, 'r', 6);
	ft_strlcpy(dest, "", 15);
	strlcpy(dest2, "", 15);
	printf("%s\n", dest);
	printf("%s\n", dest2);
}*/
