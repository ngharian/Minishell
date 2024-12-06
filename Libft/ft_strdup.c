/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:13:56 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		counter;
	int		i;

	i = 0;
	counter = 0;
	while (s1[counter] != '\0')
		counter++;
	copy = malloc((counter + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

/*int main(void)
{
	char *test;
	char *test2;
	char src[] = "coucou ca va";
	test = strdup(src);
	test2 = ft_strdup(src);
	printf("%s\n", test);
	printf("%s\n", test2);
}*/
