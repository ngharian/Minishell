/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:52:04 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_isalpha(int c)
{
	if (c < 65)
		return (0);
	if (c > 90 && c < 97)
		return (0);
	if (c > 122)
		return (0);
	return (1);
}

/*int main(int argc, char **argv)
{
	printf("%i\n", ft_isalpha(argv[1][0]));
	printf("%i\n", isalpha(argv[1][0]));
}*/
