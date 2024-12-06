/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:02:15 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

static char	*wrong_conditions(char *substring)
{
	substring = malloc(sizeof(char));
	if (substring == NULL)
		return (NULL);
	substring[0] = '\0';
	return (substring);
}

static char	*fill_substring(char *substring, \
char const *s, unsigned int start, size_t len)
{
	size_t	index;

	index = 0;
	while (s[start] != '\0' && index < len)
	{
		substring[index] = s[start];
		index++;
		start++;
	}
	substring[index] = '\0';
	return (substring);
}

static int	update_len(size_t len, char const *s, \
unsigned int start, unsigned int lenght)
{
	unsigned int	rest_lenght;

	rest_lenght = start;
	if (lenght < len)
		len = lenght;
	while (s[rest_lenght] != '\0')
		rest_lenght++;
	if ((rest_lenght - start) < len)
		len = (rest_lenght - start);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	lenght;

	lenght = 0;
	substring = NULL;
	if (len > INT_MAX)
		len = INT_MAX;
	while (s[lenght] != '\0')
		lenght++;
	if (start >= lenght || lenght == 0 || len < 1)
	{
		substring = wrong_conditions(substring);
		return (substring);
	}
	len = update_len(len, s, start, lenght);
	substring = malloc((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	substring = fill_substring(substring, s, start, len);
	return (substring);
}

/*int main(void)
{
	char	test[] = "coucou comment ca va bien";
	printf("%s\n", ft_substr("hola", 0, 18446744073709551615));
}*/
