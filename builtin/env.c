/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:11:33 by gdero             #+#    #+#             */
/*   Updated: 2024/12/06 16:29:48 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

//mode 0 == env ; mode 1 == export
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
			printf("env: %s: No such file or directory\n", cmd[1]);
			return (6);
		}
	}
	else
		temp = vars->exp;
	while (temp[++index])
		printf("%s\n", temp[index]);
	if (mode == 0)
		return (6);
	else
		return (4);
}

int	fill_env(char **env, t_env_vars *vars)
{
	int	index;

	index = 0;
	while (env[index])
		index++;
	vars->nb_string = index;
	vars->env = malloc((index + 1) * sizeof(char *));
	vars->exp = malloc((index + 1) * sizeof(char *));
	if (!vars->env || !vars->exp)
		return (1);
	vars->env[index] = NULL;
	vars->exp[index] = NULL;
	index = -1;
	while (env[++index])
	{
		vars->env[index] = ft_strdup(env[index]);
		vars->exp[index] = add_char(vars->env[index], 0);
		if (!vars->env[index] || !vars->exp[index])
			return (1);
	}
	index--;
	return (make_order(vars, index));
}
