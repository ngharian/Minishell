/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:54:14 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_isprint(int c)
{
	if (c < 32 || c > 126)
		return (0);
	return (1);
}

/*int main(int argc, char **argv)
{
	printf("%i\n", ft_isprint(argv[1][0]));
	printf("%i\n", isprint(argv[1][0]));
}*/
