/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:51:48 by gdero             #+#    #+#             */
/*   Updated: 2024/12/17 17:43:37 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	updt_line(char **input, t_env_vars *vars, char *to_find, int *index)
{
	int		new_index;
	bool	var_found;

	new_index = -1;
	var_found = false;
	while (vars->env[++new_index])
	{
		if (ft_strncmp(vars->env[new_index], to_find, ft_strlen(to_find)) == 0 \
		&& vars->env[new_index][ft_strlen(to_find)] == '=')
		{
			exchange_vars(input, vars->env[new_index], to_find, index);
			var_found = true;
		}
	}
	if (var_found == false)
		exchange_vars(input, NULL, to_find, index);
	free(to_find);
}

static void	switch_vars(char **input, t_env_vars *vars, int *index)
{
	int		str_index;
	int		new_index;
	char	*to_find;

	str_index = *index;
	while ((*input)[str_index] != ' ' && (*input)[str_index] != '\0' \
	&& (*input)[str_index] != '$' && (*input)[str_index] != '"' \
	&& (*input)[str_index] != 39 && (*input)[str_index] != '=')
		str_index++;
	new_index = str_index - *index;
	to_find = malloc((new_index + 1) * sizeof(char));
	if (!to_find)
		print_exit_error("Malloc error", NULL, 1, NULL);
	to_find[new_index] = '\0';
	while (--str_index >= *index)
		to_find[--new_index] = (*input)[str_index];
	updt_line(input, vars, to_find, index);
}

static void	dollar_case(char **input, t_env_vars *vars, int *index)
{
	if ((*input)[*index] == '?' \
	&& ((*input)[*index + 1] == ' ' || (*input)[*index + 1] == '\0'))
		exchange_vars(input, ft_itoa(vars->exit_code), "?", index);
	else if ((*input)[*index] == '$')
		exchange_vars(input, NULL, "$", index);
	else if ((*input)[*index] != ' ')
	{
		if ((*input)[*index] == '"')
			exchange_vars(input, NULL, "$", index);
		else
			switch_vars(input, vars, index);
	}
}

static void	double_quotes_case(char **input, int *index, t_env_vars *vars)
{
	if ((*input)[*index] == '"')
	{
		*index = *index + 1;
		while ((*input)[*index] != '"')
		{
			if ((*input)[*index] == '\0')
				break ;
			if ((*input)[*index] == '$')
			{
				*index = *index + 1;
				if ((*input)[*index] == ' ')
					continue ;
				if ((*input)[*index] == '\0')
					break ;
				dollar_case(input, vars, index);
				*index = *index - 1;
			}
			*index = *index + 1;
		}
	}
}

void	expander(char **input, t_env_vars *vars)
{
	int	index;

	index = -1;
	while ((*input)[++index])
	{
		double_quotes_case(input, &index, vars);
		if ((*input)[index] == 39)
			index = skip_quotes((*input), index) - 1;
		if ((*input)[index] == '\0')
			break ;
		if ((*input)[index] == '$')
		{
			index++;
			if ((*input)[index] == ' ')
				continue ;
			if ((*input)[index] == '\0')
				break ;
			dollar_case(input, vars, &index);
			index -= 1;
		}
	}
}
