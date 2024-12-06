/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:28:16 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

static int	string_len(const char *string)
{
	int	count;

	count = 0;
	while (string[count] != '\0')
		count++;
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		index;
	int		len_s1;
	int		len_s2;
	char	*newstring;

	index = 0;
	len_s1 = string_len(s1);
	len_s2 = string_len(s2);
	newstring = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		newstring[index] = *s1;
		index++;
		s1++;
	}
	while (*s2 != '\0')
	{
		newstring[index] = *s2;
		index++;
		s2++;
	}
	newstring[index] = '\0';
	return (newstring);
}

/*int main(void)
{
	char test[] = "coucou";
	char test2[] = "Ca va";
	printf("%s\n", ft_strjoin(test, test2));
}*/
