/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:11:11 by gdero             #+#    #+#             */
/*   Updated: 2023/10/19 18:11:14 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		index;
	int		lenght;
	char	*new_string;

	index = 0;
	lenght = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[lenght] != '\0')
		lenght++;
	new_string = malloc((lenght + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (index < lenght)
	{
		new_string[index] = (*f)(index, s[index]);
		index++;
	}
	new_string[index] = '\0';
	return (new_string);
}
