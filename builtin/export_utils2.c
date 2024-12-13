/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:35:29 by gdero             #+#    #+#             */
/*   Updated: 2024/12/13 13:50:31 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_or_not(int mode, char **new_env, char *str, int str_index)
{
	int	str_index2;

	if (mode == 7 || mode == 8)
	{
		(*new_env) = malloc((ft_strlen(str)) * sizeof(char));
		if (!(*new_env))
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		(*new_env)[ft_strlen(str) - 1] = '\0';
		while (str[++str_index] != '+')
			(*new_env)[str_index] = str[str_index];
		str_index2 = str_index;
		while (str[++str_index])
			(*new_env)[str_index2++] = str[str_index];
	}
	else
	{
		(*new_env) = ft_strdup(str);
		if (!(*new_env))
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
	}
}

void	add_line_to_env(char ***env, char ***new_env, char *str, int mode)
{
	int	index;

	index = 0;
	while ((*env)[index])
		index++;
	(*new_env) = malloc((index + 2) * sizeof(char *));
	if (!new_env)
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
	(*new_env)[index + 1] = NULL;
	index = -1;
	while ((*env)[++index])
	{
		(*new_env)[index] = ft_strdup((*env)[index]);
		if (!(*new_env)[index])
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
	}
	append_or_not(mode, &(*new_env)[index], str, -1);
	free_split(*env);
	(*env) = (*new_env);
}

static void	the_sixth_mode(char **oldstring, char *to_append, char **newstring)
{
	int		index;
	int		index2;
	char	*last_update;

	index = 0;
	while (to_append[index] != '=')
		index++;
	index2 = index;
	while (to_append[index2])
		index2++;
	last_update = malloc((index2 - index) * sizeof(char));
	if (!(last_update))
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
	last_update[index2 - index - 1] = '\0';
	index2 = -1;
	while (to_append[++index])
		last_update[++index2] = to_append[index];
	cmd_without_quotes(oldstring);
	(*newstring) = ft_strjoin(*oldstring, last_update);
	free(last_update);
	if (!(*newstring))
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
}

void	append_var(char **oldstring, char *to_append, int mode)
{
	int		index;
	int		index2;
	char	*newstring;

	index = -1;
	if (mode == 6)
		the_sixth_mode(oldstring, to_append, &newstring);
	else
	{
		newstring = malloc((ft_strlen(to_append)) * sizeof(char));
		if (!newstring)
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		newstring[ft_strlen(to_append) - 1] = '\0';
		while (to_append[++index] != '+')
			newstring[index] = to_append[index];
		index2 = index;
		while (to_append[++index])
			newstring[index2++] = to_append[index];
	}
	free(*oldstring);
	*oldstring = newstring;
}

void	add_to_exp(char *str, int mode, t_env_vars **vars, int *index_mode)
{
	char	**new_exp;

	new_exp = NULL;
	if (mode == 2 || mode == 5)
	{
		free((*vars)->exp[*index_mode]);
		(*vars)->exp[*index_mode] = ft_strdup(str);
		if (!(*vars)->exp[*index_mode])
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		return ;
	}
	if (mode == 6 || mode == 7)
	{
		append_var(&(*vars)->exp[*index_mode], str, mode);
		return ;
	}
	add_line_to_env(&(*vars)->exp, &new_exp, str, mode);
}
