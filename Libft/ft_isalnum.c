/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:45:59 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_isalnum(int c)
{
	if (c < 48)
		return (0);
	if (c > 57 && c < 65)
		return (0);
	if (c > 90 && c < 97)
		return (0);
	if (c > 122)
		return (0);
	return (1);
}

/*int main(int argc, char **argv)
{
	printf("%i\n", ft_isalnum(argv[1][0]));
	printf("%i\n", isalnum(argv[1][0]));
}*/
