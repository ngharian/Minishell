/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:12:51 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_bzero(void	*s, size_t n)
{
	unsigned long		i;
	char				zero;
	char				*str;

	i = 0;
	zero = 0;
	str = s;
	while (i < n)
	{
		str[i] = zero;
		i++;
	}
}

/*int main(void)
{
	char test2[] = "\0 coucou les gens";
	char test[] = "\0 coucou les gens";
	ft_bzero(test2, 3);
	bzero(test, 3);
	int i = 3;
	int j = 0;
	int k = 0;
	while (j < i)
	{
		printf("%c\n", test[j]);
		j++;
	}
	while (k < i)
	{
		printf("%c\n", test2[k]);
		k++;
	}
	//printf("%c\n", test[3]);
	//printf("%c\n", test2[3]);
}*/
