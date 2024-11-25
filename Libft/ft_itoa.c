/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:07:34 by gdero             #+#    #+#             */
/*   Updated: 2023/10/18 18:26:15 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	count_cifers(long n, int nb)
{
	int	count;

	count = 0;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	if (nb < 0)
		count++;
	return (count);
}

static char	*convert(char *ptr, long number)
{
	if (number <= 9)
	{
		*ptr = number + '0';
		return (ptr);
	}
	*ptr = (number % 10) + '0';
	return (convert (ptr + 1, number / 10));
}

static char	*invert(char *string, long cifers)
{
	int		index;
	int		end;
	char	temp;

	index = 0;
	end = cifers - 1;
	while (index < end)
	{
		temp = string[end];
		string[end] = string[index];
		string[index] = temp;
		index++;
		end--;
	}
	return (string);
}

static char	*ft_nul(char *string)
{
	string = malloc(2 * sizeof(char));
	if (string == NULL)
		return (NULL);
	string[0] = '0';
	string[1] = '\0';
	return (string);
}

char	*ft_itoa(int n)
{
	long	nb_cifers;
	long	nb;
	char	*string;
	char	*cifer;

	nb = n;
	string = NULL;
	if (n == 0)
	{
		string = ft_nul(string);
		return (string);
	}
	if (nb < 0)
		nb *= -1;
	nb_cifers = count_cifers(nb, n);
	string = malloc((nb_cifers + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	string[nb_cifers] = '\0';
	if (n < 0)
		string[nb_cifers - 1] = '-';
	cifer = string;
	string = convert(string, nb);
	cifer = invert(cifer, nb_cifers);
	return (cifer);
}

/*int main(void)
{
    int i = INT_MIN;
    printf("%s\n", ft_itoa(i));
}*/