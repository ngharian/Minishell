/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:00:47 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:33:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		i;
	char		*ptr;

	i = 0;
	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

/*int main(void)
{
	int	size = 8539;

	void *d1 = ft_calloc(size, sizeof(int));
	void *d2 = calloc (size, sizeof(int));
	printf("%i\n", memcmp(d1, d2, size * sizeof(int)));
	if (memcmp(d1, d2, size * sizeof(int)))
		return (printf("coucou"));
	free (d1);
	free (d2);
	printf("%lu\n", SIZE_MAX);
}*/