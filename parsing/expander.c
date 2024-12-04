/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:51:48 by gdero             #+#    #+#             */
/*   Updated: 2024/12/04 17:40:12 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	updt_line(char **input, t_env_vars *vars, char *to_find, int *index)
{
	int		new_index;
	int		index_var;
	bool	var_found;

	new_index = -1;
	var_found = false;
	while (vars->env[++new_index])
	{
		index_var = 0;
		if (ft_strncmp(vars->env[new_index], to_find, ft_strlen(to_find)) == 0 \
		&& vars->env[new_index][ft_strlen(to_find)] == '=')
		{
			if (exchange_vars(input, vars->env[new_index], to_find, index))
				return (1);
			var_found = true;
		}
	}
	if (var_found == false)
		exchange_vars(input, NULL, to_find, index);
	free(to_find);
	return (0);
}

static int	switch_vars(char **input, t_env_vars *vars, int *index)
{
	int		str_index;
	int		new_index;
	char	*to_find;

	str_index = *index;
	while ((*input)[str_index] != ' ' && (*input)[str_index] != '\0' \
	&& (*input)[str_index] != '$' && (*input)[str_index] != '"' \
	&& (*input)[str_index] != 39 && (*input)[str_index] != '=') //ajout dernier truc
		str_index++;
	new_index = str_index - *index;
	to_find = malloc((new_index + 1) * sizeof(char));
	if (!to_find)
		return (1);
	to_find[new_index] = '\0';
	while (--str_index >= *index)
		to_find[--new_index] = (*input)[str_index];
	if (updt_line(input, vars, to_find, index))
		return (1);
	return (0);
}

static int	dollar_case(char **input, t_env_vars *vars, int *index)
{
	if ((*input)[*index] == '?' \
	&& ((*input)[*index + 1] == ' ' || (*input)[*index + 1] == '\0'))
	{
		if (exchange_vars(input, ft_itoa(vars->exit_code), "?", index))
			return (1);
	}
	else if ((*input)[*index] == '$')
	{
		if (exchange_vars(input, ft_itoa(vars->pid), "$", index))
			return (1);
	}
	else if ((*input)[*index] != ' ')
	{
		if ((*input)[*index] == '"')
			exchange_vars(input, NULL, "$", index);
		else if (switch_vars(input, vars, index))
			return (1);
	}
	return (0);
}

static int	double_quotes_case(char **input, int index, t_env_vars *vars)
{
	if ((*input)[index] == '"')
	{
		index++;
		while ((*input)[index] != '"')
		{
			if ((*input)[index] == '\0')
				break ;
			if ((*input)[index] == '$')
			{
				index++;
				if ((*input)[index] == ' ')
					continue ;
				if ((*input)[index] == '\0')
					break ;
				if (dollar_case(input, vars, &index))
					return (1);
				index -= 1;
			}
			index++;
		}
	}
	return (0);
}

int	expander(char **input, t_env_vars *vars)
{
	int	index;

	index = -1;
	while ((*input)[++index])
	{
		if (double_quotes_case(input, index, vars))
			return (1);
		if ((*input)[index] == 39)
			index = skip_quotes((*input), index);
		if ((*input)[index] == '\0')
			break ;
		if ((*input)[index] == '$')
		{
			index++;
			if ((*input)[index] == ' ')
				continue ;
			if ((*input)[index] == '\0')
				break ;
			if (dollar_case(input, vars, &index))
				return (1);
			index -= 1;
		}
	}
	return (0);
}
