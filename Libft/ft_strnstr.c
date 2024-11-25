/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:27:45 by gdero             #+#    #+#             */
/*   Updated: 2023/10/18 16:00:42 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cmpstr(char *string, char *to_find)
{
	int	i;

	i = 0;
	while (string[i] != '\0' && to_find[i] != '\0')
	{
		if (string[i] != to_find[i])
			return (string[i] - to_find[i]);
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	size_t	j;
	char	*string;
	char	*to_find;

	i = 0;
	j = 0;
	string = (char *) haystack;
	to_find = (char *) needle;
	if (*to_find == '\0')
		return (string);
	while (to_find[j] != '\0')
		j++;
	while (*string != '\0' && len >= j)
	{
		if (*string == *to_find && cmpstr(string, to_find) == 0)
			return (string);
		string++;
		i++;
		len--;
	}
	return (NULL);
}

/*int main(void)
{
	char haystack[] = "coucou ca va";
	char needle[] = "ca va";
	printf("%s\n", strnstr(haystack, needle, 20));
	printf("%s\n", ft_strnstr(haystack, needle, 20));
}*/
