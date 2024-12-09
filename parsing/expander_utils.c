/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:41:26 by gdero             #+#    #+#             */
/*   Updated: 2024/12/09 18:00:39 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	lenght_newstring(char *input, char *to_find, char *var)
{
	int	index;
	int	counter;
	int	new_lenght;

	index = -1;
	counter = 0;
	while (var[++index])
	{
		if (var[index] == ' ')
			counter++;
	}
	new_lenght = ft_strlen(input) - ft_strlen(to_find) \
	+ ft_strlen(var) + counter;
	return (new_lenght);
}

static void	new_input(char *input, char **var, int *index, bool *malloked)
{
	if ((*var) != NULL && !ft_isdigit((*var)[0]))
	{
		(*var) = ft_strdup(ft_strchr((*var), '='));
		if (!(*var))
			print_exit_error("Malloc error", NULL, 1, NULL);
		if (input[*index - 1] != 7)
			(*var)[0] = 7;
		else
			(*var)[0] = ' ';
		*malloked = true;
	}
	else if ((*var) == NULL)
		(*var) = "\0";
}

static void	copy_var(char **new_string, char *var, int *str_index, int *index)
{
	int	index_var;

	index_var = -1;
	while (var[++index_var])
	{
		if (var[index_var] == ' ')
		{
			(*new_string)[(*str_index)++] = ' ';
			(*new_string)[(*str_index)++] = 7;
		}
		else
			(*new_string)[(*str_index)++] = var[index_var];
	}
	*index = *str_index;
}

void	exchange_vars(char **input, char *var, char *to_find, int *index)
{
	int		str_index;
	int		str_index2;
	char	*new_string;
	bool	malloked;

	str_index = -1;
	malloked = false;
	new_input(*input, &var, index, &malloked);
	new_string = malloc((lenght_newstring((*input), to_find, var)) \
	* sizeof(char));
	if (!new_string)
		print_exit_error("Malloc error", NULL, 1, NULL);
	new_string[lenght_newstring((*input), to_find, var) - 1] = '\0';
	while (++str_index < *index - 1)
		new_string[str_index] = (*input)[str_index];
	str_index2 = str_index + ft_strlen(to_find);
	copy_var(&new_string, var, &str_index, index);
	while ((*input)[++str_index2])
		new_string[str_index++] = (*input)[str_index2];
	free((*input));
	if (malloked == true)
		free(var);
	*input = new_string;
}
