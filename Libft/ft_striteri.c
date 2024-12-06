/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:00:33 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	index;
	int	lenght;

	index = 0;
	lenght = 0;
	if (s == 0 || (*f) == 0)
		return ;
	while (s[lenght] != '\0')
		lenght++;
	while (index < lenght)
	{
		(*f)(index, s);
		s++;
		index++;
	}
}
