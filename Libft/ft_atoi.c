/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:30:35 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

unsigned long long	ft_atoi(const char *str)
{
	int					neg;
	unsigned long long	result;

	neg = 1;
	result = 0;
	while (*str == 32 || ((*str > 8 && *str < 14)))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = neg * -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		result = 10 * result + (*str - '0');
		str++;
	}
	if (result == 2147483648 && neg == -1)
		return (-2147483648);
	return (result * neg);
}

/*int main(void)
{
	char test[] = "55555555";
	printf("%i\n", atoi(test));
	printf("%i\n", ft_atoi(test));
}*/
