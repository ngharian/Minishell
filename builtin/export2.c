/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:27:29 by gdero             #+#    #+#             */
/*   Updated: 2024/12/06 17:32:52 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	does_exist(char *temp, int index_str, char *str)
{
	if (str[index_str] == '\0' && \
	(temp[index_str] == '\0' || temp[index_str] == '='))
		return (1);
	if (str[index_str] == '+' && temp[index_str] == '=')
		return (6);
	if (str[index_str] == '=' && temp[index_str] == '=')
		return (2);
	if (str[index_str] == '+' && temp[index_str] == '\0')
		return (7);
	if (str[index_str] == '=' && temp[index_str] == '\0')
		return (5);
	return (0);
}

int	already_exists(char *str, t_env_vars **vars, \
int *index_mode, int index_str)
{
	int		index;
	char	*temp;

	index = -1;
	while ((*vars)->exp[++index])
	{
		temp = (*vars)->exp[index] + 11;
		if (ft_strncmp(str, temp, index_str) == 0)
		{
			*index_mode = index;
			return (does_exist(temp, index_str, str));
		}
	}
	*index_mode = -1;
	if (is_there_equal(str, 0))
	{
		if (str[index_str] == '+' && str[index_str - 1] != '=')
			return (8);
		return (3);
	}
	return (4);
}

char	*add_char(char *env, int mode)
{
	int		index;
	int		index2;
	char	*newstring;
	char	*finalstring;

	index = -1;
	finalstring = NULL;
	newstring = malloc((ft_strlen(env) + 3) * sizeof(char));
	if (!newstring)
		return (NULL);
	newstring[ft_strlen(env) + 2] = '\0';
	while (env[++index] != '=')
		newstring[index] = env[index];
	index2 = index;
	newstring[index] = '=';
	newstring[++index] = '"';
	while (env[++index2])
		newstring[++index] = env[index2];
	newstring[index + 1] = '"';
	if (mode != 6)
		finalstring = ft_strjoin("declare -x ", newstring);
	else
		finalstring = ft_strdup(newstring);
	free(newstring);
	if (!finalstring)
		return (NULL);
	return (finalstring);
}

int	make_order(t_env_vars *vars, int index)
{
	int		j;
	char	*temp;
	int		ind2;
	int		ind3;

	while (index >= 0)
	{
		j = index - 1;
		ind2 = is_there_equal(vars->exp[index], 1);
		while (j >= 0)
		{
			ind3 = is_there_equal(vars->exp[j], 1);
			if (ind3 < ind2)
				ind3 = ind2;
			if (ft_memcmp(vars->exp[index], vars->exp[j], ind3) < 0)
			{
				temp = vars->exp[index];
				vars->exp[index] = vars->exp[j];
				vars->exp[j] = temp;
			}
			j--;
		}
		index--;
	}
	return (0);
}
