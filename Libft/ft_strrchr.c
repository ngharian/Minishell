/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:15:05 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*string;
	char	a;

	i = 0;
	string = (char *) s;
	a = (char) c;
	while (string[i] != '\0')
	{
		i++;
	}
	while (string[i] != a && i >= 0)
	{
		if (i == 0)
			return (0);
		i--;
	}
	string = (string + i);
	return (string);
}

/*int main(void)
{
	char test[] = "joucou comment ca va ?";
	printf("%s\n", strrchr(test, '\0'));
	printf("%s\n", ft_strrchr(test, '\0'));
}*/
