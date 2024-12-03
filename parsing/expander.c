/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:51:48 by gdero             #+#    #+#             */
/*   Updated: 2024/12/03 19:14:15 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exchange_vars(char **input, char *var, char *to_find, int *index)
{
	int		str_index;
	int		str_index2;
	int		index_var;
	int		new_lenght;
	char	*new_string;
	bool	malloked;
	int		space_counter = 0;

	str_index = -1;
	malloked = false;
	if (var != NULL && !ft_isdigit(var[0]))
	{
		var = ft_strdup(ft_strchr(var, '='));
		while (var[++str_index])
		{
			if (var[str_index] == ' ')
				space_counter++;
		}
		str_index = -1;
		if (!var)
			return (1);
		if ((*input)[*index - 1] != 7)
			var[0] = 7;
		else
			var[0] = ' ';
		malloked = true;
	}
	else if (var == NULL)
		var = "\0";
	new_lenght = ft_strlen((*input)) - ft_strlen(to_find) + ft_strlen(var) + space_counter;
	new_string = malloc((new_lenght) * sizeof(char));
	if (!new_string)
		return (1);
	new_string[new_lenght - 1] = '\0';
	while (++str_index < *index - 1)
		new_string[str_index] = (*input)[str_index];
	str_index2 = str_index + ft_strlen(to_find);
	index_var = -1;
	while (var[++index_var])
	{
		if (var[index_var] == ' ')
		{
			new_string[str_index++] = ' ';
			new_string[str_index++] = 7;
		}
		else
			new_string[str_index++] = var[index_var];
	}
	*index = str_index;
	while ((*input)[++str_index2])
		new_string[str_index++] = (*input)[str_index2];
	free((*input));
	if (malloked == true)
		free(var);
	*input = new_string;
	return (0);
}

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
	&& (*input)[str_index] != 39)
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

int	expander(char **input, t_env_vars *vars)
{
	int	index;

	index = -1;
	while ((*input)[++index])
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
					//index -= 1;
				}
				index++;
			}
		}
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
