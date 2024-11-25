/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:34:49 by gdero             #+#    #+#             */
/*   Updated: 2023/10/18 15:15:30 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*concat(char *dst, size_t dstsize, const char *src, size_t len_dst)
{
	size_t	i;
	int		j;

	i = 0;
	j = len_dst;
	while (i < (dstsize - len_dst - 1) && src[i] != '\0')
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		len_dst;
	size_t		len_src;

	len_dst = 0;
	len_src = 0;
	while (src[len_src] != '\0')
		len_src++;
	if (dst == NULL && dstsize == 0)
		return (len_src);
	while (dst[len_dst] != '\0' && len_dst < dstsize)
		len_dst++;
	if (len_dst == dstsize)
		return (len_dst + len_src);
	dst = concat(dst, dstsize, src, len_dst);
	return (len_dst + len_src);
}

/*int main(void)
{
	int i = 0;
	int j = 0;
	char *dst = "coucou";
	char *dst2 = "coucou";
	const char *src = "hello les gens";
	printf("%lu\n", strlcat(dst, src, 6));
	printf("%lu\n", ft_strlcat(dst2, src, 6));
	printf("%s\n", dst);
	printf("%s\n", dst2);
}*/
