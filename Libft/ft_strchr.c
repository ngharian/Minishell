/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:53:29 by gdero             #+#    #+#             */
/*   Updated: 2024/10/31 17:32:30 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*string;
	char	a;

	if (!s)
		return (NULL);
	string = (char *) s;
	a = (char) c;
	while (*string != a)
	{
		if (*string == '\0')
			return (0);
		string++;
	}
	return (string);
}

/*int main(void)
{
	char test[] = "coucou comment ca va ?";
	printf("%s\n", strchr(test, '\0'));
	printf("%s\n", ft_strchr(test, '\0'));
}*/
