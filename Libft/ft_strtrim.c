/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:45:16 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:34:03 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

static int	check_set(char c, char const *set)
{
	int	i;
	int	len_set;

	i = 0;
	len_set = ft_strlen(set);
	while (i < len_set)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	set_count(char const *string, char const *set, int lenght)
{
	int	counter;

	counter = 0;
	while (*string != '\0')
	{
		while (check_set(*string, set) == 1)
		{
			counter++;
			string++;
		}
		break ;
	}
	if (counter == lenght)
		return (lenght);
	while (*string != '\0')
		string++;
	string--;
	while (check_set(*string, set) == 1)
	{
		counter++;
		string--;
	}
	return (counter);
}

static char	*copy(char *copy, char const *string, char const *set, int lenght)
{
	int	index;

	index = 0;
	while (*string != 0)
	{
		while (check_set(*string, set) == 1)
			string++;
		while (index < lenght)
		{
			copy[index] = *string;
			index++;
			string++;
		}
		break ;
	}
	copy[index] = '\0';
	return (copy);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		lenght;
	int		lenghtdel;
	char	*trimmed_string;

	if (s1 == NULL || set == NULL)
		return (NULL);
	lenght = ft_strlen(s1);
	lenghtdel = set_count(s1, set, lenght);
	trimmed_string = (char *) s1;
	if (lenght - lenghtdel == 0)
	{
		trimmed_string = malloc(sizeof(char));
		if (trimmed_string == NULL)
			return (NULL);
		trimmed_string[0] = '\0';
		return (trimmed_string);
	}
	trimmed_string = malloc(((lenght - lenghtdel) + 1) * sizeof(char));
	if (trimmed_string == NULL)
		return (NULL);
	trimmed_string = copy(trimmed_string, s1, set, (lenght - lenghtdel));
	return (trimmed_string);
}

/*int	main(void)
{
	char	*finish;
	char	string[] = " \t \t \n  \n\n\n\t";
	char	set[] = " \n\t";

	finish = ft_strtrim(string, set);
	printf("%s\n", finish);
}*/