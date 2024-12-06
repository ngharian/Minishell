/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:57:31 by ngharian          #+#    #+#             */
/*   Updated: 2023/09/14 11:10:14 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i ++;
	}
	return (s1[i] - s2[i]);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str1[] = "abcdef";
	char	str2[] = "abcdeg";
	printf("%d", ft_strcmp(str1, str2));
}*/
