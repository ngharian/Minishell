/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:10:16 by gdero             #+#    #+#             */
/*   Updated: 2024/12/13 15:10:53 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static int	check_first_arg(char *arg)
{
	int	index;

	index = -1;
	while (arg[++index])
	{
		if (arg[index] != '-' && arg[index] != 'n')
			return (1);
	}
	index = -1;
	while (arg[++index])
	{
		if (arg[index] != '-')
			return (0);
	}
	return (1);
}

static void	check_for_n(char **cmd, int *index, bool *must_new_line)
{
	int	nb_char;

	if (check_first_arg(cmd[1]))
		return ;
	while (cmd[*index] && strncmp(cmd[*index], "-", 1) == 0)
	{
		nb_char = 1;
		while (cmd[*index][nb_char])
		{
			if (cmd[*index][nb_char] != 'n')
				return ;
			nb_char++;
		}
		*must_new_line = false;
		*index = *index + 1;
	}
	return ;
}

int	ft_echo(char **cmd, t_env_vars *vars, int index)
{
	bool	must_new_line;

	must_new_line = true;
	if (cmd[index])
		check_for_n(cmd, &index, &must_new_line);
	while (cmd[index])
	{
		if (!cmd[index + 1])
		{
			if (cmd[index][0] == '~' && !cmd[index][1])
				printf("%s", get_path_line(vars->env, "HOME=", 0));
			else
				printf("%s", cmd[index]);
			break ;
		}
		if (cmd[index][0] == '~' && !cmd[index][1])
			printf("%s ", get_path_line(vars->env, "HOME=", 0));
		else
			printf("%s ", cmd[index]);
		index++;
	}
	if (must_new_line)
		printf("\n");
	return (0);
}
