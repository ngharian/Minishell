/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:42:27 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

/*int main(int argc, char **argv)
{
	printf("%i\n", ft_isdigit(argv[1][0]));
	printf("%i\n", isdigit(argv[1][0]));
}*/
