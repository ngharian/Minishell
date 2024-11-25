/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:49:41 by gdero             #+#    #+#             */
/*   Updated: 2023/10/20 11:49:43 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	reverse_nb(long nb)
{
	long	reverse;
	long	rest;

	reverse = 0;
	while (nb != 0)
	{
		rest = nb % 10;
		reverse = reverse * 10 + rest;
		nb /= 10;
	}
	return (reverse);
}

static long	count_digits(long nb)
{
	long	digits;

	digits = 0;
	while (nb > 0)
	{
		nb /= 10;
		digits++;
	}
	return (digits);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;
	long	digits;

	nb = n;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	digits = count_digits(nb);
	nb = reverse_nb(nb);
	while (digits--)
	{
		c = (nb % 10) + '0';
		write(fd, &c, 1);
		nb /= 10;
	}
}
