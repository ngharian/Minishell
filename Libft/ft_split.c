/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:07:34 by gdero             #+#    #+#             */
/*   Updated: 2024/03/26 12:03:49 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free(char **array, int index)
{
	if (array[index] == NULL)
	{
		while (index >= 0)
		{
			free(array[index]);
			index--;
		}
		free(array);
		return (1);
	}
	return (0);
}

static long	nb_split(char const *string, char sep)
{
	long	counter;

	counter = 0;
	while (*string != '\0')
	{
		while (*string == sep && *string != '\0')
			string++;
		if (*string != '\0')
			counter++;
		while (*string != sep && *string != '\0')
			string++;
	}
	return (counter);
}

static int	len_split(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static char	*fill_array(char const *s, char c)
{
	int		index;
	int		len;
	char	*new_string;

	index = 0;
	len = len_split(s, c);
	new_string = malloc((len + 1) * (sizeof(char)));
	if (new_string == NULL)
	{
		free(new_string);
		return (NULL);
	}
	while (index < len)
	{
		new_string[index] = *s;
		index++;
		s++;
	}
	new_string[index] = '\0';
	return (new_string);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	char	**array;

	index = 0;
	if (s == NULL)
		return (NULL);
	array = malloc((nb_split(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
		{
			array[index] = fill_array(s, c);
			if (ft_free(array, index) == 1)
				return (NULL);
			index++;
		}
		while (*s != c && *s != '\0')
			s++;
	}
	array[index] = NULL;
	return (array);
}

/*int main(void)
{
	char **final_array;
	char test[] = " Hello    le   monde";
	final_array = ft_split("ello!", ' ');
	for (int i = 0; i < 2; i++)
	{
		printf("%s\n", final_array[i]);
	}
	free(final_array);
}*/
