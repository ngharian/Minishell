/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:11:33 by gdero             #+#    #+#             */
/*   Updated: 2024/12/13 15:10:56 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	ft_env(char **cmd, t_env_vars *vars, int mode)
{
	int		index;
	char	**temp;

	index = -1;
	if (mode == 0)
	{
		temp = vars->env;
		if (cmd[1])
		{
			print_exit_error("No such file or directory", cmd[1], -1, "env: ");
			return (127);
		}
	}
	else
		temp = vars->exp;
	while (temp[++index])
		printf("%s\n", temp[index]);
	return (0);
}

void	add_char(char **env, int mode)
{
	int		index;
	int		index2;
	char	*newstring;

	index = -1;
	newstring = malloc((ft_strlen(*env) + 3) * sizeof(char));
	if (!newstring)
		print_exit_error("Malloc error", NULL, 1, NULL);
	newstring[ft_strlen((*env)) + 2] = '\0';
	while ((*env)[++index] != '=')
		newstring[index] = (*env)[index];
	index2 = index;
	newstring[index] = '=';
	newstring[++index] = '"';
	while ((*env)[++index2])
		newstring[++index] = (*env)[index2];
	newstring[index + 1] = '"';
	free((*env));
	if (mode != 6)
		(*env) = ft_strjoin("declare -x ", newstring);
	else
		(*env) = ft_strdup(newstring);
	free(newstring);
	if (!(*env))
		print_exit_error("Malloc error", NULL, 1, NULL);
}

void	make_order(t_env_vars *vars, int index)
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
}

void	fill_env(char **env, t_env_vars *vars)
{
	int	index;

	index = 0;
	while (env[index])
		index++;
	vars->nb_string = index;
	vars->env = malloc((index + 1) * sizeof(char *));
	vars->exp = malloc((index + 1) * sizeof(char *));
	if (!vars->env || !vars->exp)
		print_exit_error("Malloc error", NULL, 1, NULL);
	vars->env[index] = NULL;
	vars->exp[index] = NULL;
	index = -1;
	while (env[++index])
	{
		vars->env[index] = ft_strdup(env[index]);
		vars->exp[index] = ft_strdup(env[index]);
		if (!vars->env[index] || !vars->exp[index])
			print_exit_error("Malloc error", NULL, 1, NULL);
		add_char(&vars->exp[index], 0);
	}
	index--;
	return (make_order(vars, index));
}
