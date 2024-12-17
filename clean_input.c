/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:39:42 by gdero             #+#    #+#             */
/*   Updated: 2024/12/17 17:44:07 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_clean_str(char *str)
{
	int	i;
	int	cond;
	int	counter;

	cond = 0;
	i = 0;
	counter = 0;
	while (str[i])
	{
		++counter;
		if (str[i] == 6 || str[i] == 7)
		{
			cond = 1;
			--counter;
		}
		++i;
	}
	if (cond == 0)
		return (-1);
	return (counter);
}

char	**clean_args(char **split, int i, int index, int j)
{
	int		counter;
	char	*new_str;

	while (split[++i])
	{
		j = -1;
		index = -1;
		counter = count_clean_str(split[i]);
		if (counter == -1)
			continue ;
		new_str = malloc(sizeof(char) * (counter + 1));
		if (!new_str)
			print_exit_error("Malloc error", NULL, 1, NULL);
		while (split[i][++j])
		{
			if (split[i][j] == 7 || split[i][j] == 6)
				continue ;
			new_str[++index] = split[i][j];
		}
		new_str[++index] = '\0';
		free(split[i]);
		split[i] = new_str;
	}
	return (split);
}
