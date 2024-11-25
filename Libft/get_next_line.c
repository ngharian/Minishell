/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:36:32 by gdero             #+#    #+#             */
/*   Updated: 2024/03/04 13:52:23 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*copy_newline(char *s1, int counter)
{
	char	*final_copy;
	int		i;

	i = 0;
	final_copy = malloc((counter + 2) * sizeof(char));
	if (final_copy == NULL)
		return (NULL);
	while (s1[i] != '\n')
	{
		final_copy[i] = s1[i];
		i++;
	}
	final_copy[i] = '\n';
	final_copy[i + 1] = '\0';
	return (final_copy);
}

char	*copy_classic(char *s1, int counter)
{
	char	*final_copy;
	int		i;

	i = 0;
	final_copy = malloc((counter + 1) * sizeof(char));
	if (final_copy == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		final_copy[i] = s1[i];
		i++;
	}
	final_copy[i] = '\0';
	return (final_copy);
}

char	*ft_strdup_gnl(char *s1)
{
	char	*copy;
	int		counter;

	counter = 0;
	if (!s1[0])
		return (NULL);
	while (s1[counter] != '\0' && s1[counter] != '\n')
		counter++;
	if (s1[counter] == '\n')
	{
		copy = copy_newline(s1, counter);
		if (copy == NULL)
			return (NULL);
		counter++;
	}
	else
	{
		copy = copy_classic(s1, counter);
		if (copy == NULL)
			return (NULL);
	}
	return (copy);
}

char	*read_line(int fd, char *next_line)
{
	char	*buffer;
	ssize_t	i;

	i = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(next_line);
		return (NULL);
	}
	while (i != 0 && !ft_strchr_gnl(next_line, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			free(next_line);
			return (NULL);
		}
		buffer[i] = '\0';
		next_line = ft_strjoin_gnl(next_line, buffer);
	}
	free(buffer);
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*next_line;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	next_line = read_line(fd, next_line);
	if (next_line == NULL)
		return (NULL);
	line = ft_strdup_gnl(next_line);
	if (line == NULL)
	{
		free(next_line);
		next_line = NULL;
		return (NULL);
	}
	next_line = update_line(next_line);
	return (line);
}

/*int	main(int argc, char **argv)
{
	(void) argc;
	int		fd;
	char	*test;

	test = NULL;
	fd = open(argv[1], O_RDONLY);
	test = get_next_line(fd);
	printf("%s", test);
	free(test);
	test = get_next_line(fd);
	printf("%s", test);
	free(test);
	test = get_next_line(fd);
	printf("%s", test);
	free(test);
	test = get_next_line(fd);
	printf("%s", test);
	free(test);
	test = get_next_line(fd);
	printf("%s", test);
	free(test);
	test = get_next_line(fd);
	printf("%s", test);
	free(test);
	test = get_next_line(fd);
	printf("%s", test);
	free(test);
	test = get_next_line(fd);
	printf("%s", test);
	free(test);
}*/
