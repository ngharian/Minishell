/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:44:41 by gdero             #+#    #+#             */
/*   Updated: 2024/03/04 13:53:43 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	string_len_gnl(char *string)
{
	int	count;

	count = 0;
	if (!string)
		return (0);
	while (string[count] != '\0')
		count++;
	return (count);
}

char	*copy_the_f_line(char *s1, char *s2, char *newstring)
{
	int	index;
	int	index2;

	index = 0;
	index2 = 0;
	while (s1[index] != '\0')
	{
		newstring[index] = s1[index];
		index++;
	}
	while (s2[index2] != '\0')
	{
		newstring[index] = s2[index2];
		index++;
		index2++;
	}
	newstring[index] = '\0';
	return (newstring);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*newstring;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	newstring = malloc((string_len_gnl(s1) + \
	string_len_gnl(s2) + 1) * sizeof(char));
	if (newstring == NULL)
	{
		free(s1);
		return (NULL);
	}
	newstring = copy_the_f_line(s1, s2, newstring);
	free(s1);
	return (newstring);
}

char	*ft_strchr_gnl(char *s, int c)
{
	char	a;

	a = (char) c;
	if (!s)
		return (NULL);
	if (*s == '\0')
		return (NULL);
	while (*s != a)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	if (*s + 1 == 0)
	{
		free (s);
		return (NULL);
	}
	return (s + 1);
}

char	*update_line(char *next_line)
{
	int		i;
	int		j;
	char	*update;

	i = 0;
	while (next_line[i] != '\0' && next_line[i] != '\n')
		i++;
	if (!next_line[i])
	{
		free(next_line);
		return (NULL);
	}
	update = (char *)malloc(sizeof(char) * (string_len_gnl(next_line) - i + 1));
	if (!update)
	{
		free(next_line);
		return (NULL);
	}
	i++;
	j = 0;
	while (next_line[i])
		update[j++] = next_line[i++];
	update[j] = '\0';
	free(next_line);
	return (update);
}
