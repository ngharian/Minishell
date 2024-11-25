/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:17:02 by gdero             #+#    #+#             */
/*   Updated: 2023/10/20 12:17:04 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	unsigned long	index;

	index = 0;
	if (s == NULL)
		return ;
	while (index < ft_strlen(s))
	{
		write(fd, &s[index], 1);
		index++;
	}
	write(fd, "\n", 1);
}
