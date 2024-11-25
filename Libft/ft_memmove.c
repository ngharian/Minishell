/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:36:05 by gdero             #+#    #+#             */
/*   Updated: 2023/10/17 13:23:34 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	move_end(unsigned char *d, unsigned char *s, size_t len)
{
	d = d + len - 1;
	s = s + len - 1;
	while (len != 0)
	{
		*d = *s;
		d--;
		s--;
		len--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	if (d == s)
		return (dst);
	if (d < s || d >= s + len)
	{
		while (len != 0)
		{
			*d = *s;
			d++;
			s++;
			len--;
		}
		return (dst);
	}
	else
	{
		move_end(d, s, len);
		return (dst);
	}
}

/*int	main(void)
{
	char test[6] = "coucou";
	char test2[6] = "coucou";
	char src[] = "Salut comment ca va";
	char src2[] = "Salut comment ca va";
	//memmove(src, src, 6);
	ft_memmove(src, src, 6);
	printf("%s\n", test);
	//printf("%s\n", src);
	//printf("%s\n", test2);
	//printf("%s\n", src2);
}*/

/*int main(void)
{
	char dest[] = "Lorem ipsum dolor sit a";
	if (dest != ft_memmove(dest, "consectetur", 5))
		write (1, "dest's adress was not returned\n", 31);
	write(1, dest, 22);
}*/
