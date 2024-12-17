/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:07:34 by gdero             #+#    #+#             */
/*   Updated: 2024/12/17 17:47:22 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	skip_quotes(char *str, int str_j)
{
	char	quote;

	quote = str[str_j++];
	while (str[str_j] != quote && str[str_j])
		++str_j;
	if (str[str_j] == '\0')
		return (str_j);
	return (++str_j);
}

static char	*ft_fill(int str_i, int str_j, char *str)
{
	char	*dest;
	int		dest_i;

	dest_i = 0;
	dest = malloc(sizeof(char) * (str_j - str_i + 1));
	if (dest == NULL)
		return (NULL);
	while (str_i < str_j)
	{
		dest[dest_i] = str[str_i];
		++dest_i;
		++str_i;
	}
	dest[dest_i] = '\0';
	return (dest);
}

static int	count_splits(char *str, char to_split, size_t index)
{
	int		counter;

	counter = 0;
	while (str[index] == ' ')
		index++;
	while (index < ft_strlen(str))
	{
		if (str[index] == 39 || str[index] == '"')
			index = skip_quotes(str, index) - 1;
		if (str[index] == to_split || str[index] == '\0')
		{
			counter++;
			while (str[index] == to_split)
				index++;
			if (str[index] == '\0')
			{
				counter--;
				break ;
			}
			continue ;
		}
		index++;
	}
	return (counter);
}

static int	fill_split(char *str, char ***array, char to_split, size_t str_j)
{
	int	array_i;
	int	str_i;

	array_i = 0;
	str_i = str_j;
	while (str_j < ft_strlen(str) + 1)
	{
		if (str[str_j] == 39 || str[str_j] == '"')
			str_j = skip_quotes(str, str_j) - 1;
		if (str[str_j] == to_split || str[str_j] == '\0')
		{
			(*array)[array_i] = ft_fill(str_i, str_j, str);
			if ((*array)[array_i++] == NULL)
				return (1);
			if (str[str_j] == '\0')
				break ;
			while (str[str_j] == to_split)
				str_j++;
			str_i = str_j;
			continue ;
		}
		str_j++;
	}
	return (0);
}

int	split_mini(char *str, char ***array, char to_split)
{
	size_t	str_j;
	int		nb_split;

	str_j = 0;
	nb_split = count_splits(str, to_split, 0);
	*array = malloc(sizeof(char *) * (nb_split + 2));
	if (!(*array))
		return (1);
	while (str[str_j] == ' ')
		str_j++;
	if (fill_split(str, array, to_split, str_j))
	{
		free_split(*array);
		return (2);
	}
	(*array)[nb_split + 1] = NULL;
	return (0);
}
