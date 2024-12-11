/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:27:29 by gdero             #+#    #+#             */
/*   Updated: 2024/12/11 14:44:03 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	new_index_mode(char *str, char **env)
{
	int		index;
	int		str_index;
	char	*temp;

	index = -1;
	str_index = 0;
	while (str[str_index] != '+' \
	&& str[str_index] != '=' && str[str_index] != '\0')
		str_index++;
	while (env[++index])
	{
		temp = env[index];
		if (ft_strncmp(str, temp, str_index) == 0 && temp[str_index] == '=')
			return (index);
	}
	return (0);
}

static void	add_to_env(char *str, int mode, t_env_vars **vars)
{
	int		index;
	char	**new_env;

	new_env = NULL;
	index = new_index_mode(str, (*vars)->env);
	if (mode == 4 || mode == 9)
		return ;
	if (mode == 2)
	{
		free((*vars)->env[index]);
		(*vars)->env[index] = ft_strdup(str);
		if (!(*vars)->env[index])
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		return ;
	}
	if (mode == 6)
	{
		append_var(&(*vars)->env[index], str, mode);
		return ;
	}
	add_line_to_env(&(*vars)->env, &new_env, str, mode);
}

void	add_to_var(char *str, int mode, t_env_vars **vars, int *index_mode)
{
	int		index;
	char	*temp;

	index = 0;
	if (mode == 1)
		return ;
	add_to_exp(str, mode, vars, index_mode);
	add_to_env(str, mode, vars);
	while ((*vars)->exp[index])
		index++;
	index--;
	if (mode == 3 || mode == 8)
		add_char(&(*vars)->exp[index], mode);
	if (mode == 4)
	{
		temp = (*vars)->exp[index];
		(*vars)->exp[index] = ft_strjoin("declare -x ", temp);
		free(temp);
	}
	if (!(*vars)->exp[index])
		print_exit_error("Malloc error", NULL, 1, NULL);
	if (mode == 2 || mode == 5 || mode == 6 || mode == 7)
		add_char(&(*vars)->exp[*index_mode], mode);
	return (make_order(*vars, index));
}
