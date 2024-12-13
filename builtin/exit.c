/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:12:28 by gdero             #+#    #+#             */
/*   Updated: 2024/12/13 15:10:59 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static int	exit_args(t_commands *cmd)
{
	int	index;

	if (cmd->cmd[1])
	{
		index = -1;
		while (cmd->cmd[1][++index])
		{
			if ((!ft_isdigit(cmd->cmd[1][index])) && (cmd->cmd[1][0] != '-'))
			{
				printf("exit\nminishell: exit: numeric argument required\n");
				exit(255);
			}
		}
		if (cmd->cmd[1][0] == '-' && !isdigit(cmd->cmd[1][1]))
		{
			printf("exit\nminishell: exit: numeric argument required\n");
			exit(255);
		}
		if (cmd->cmd[2])
		{
			printf("exit\nminishell: exit: too many arguments\n");
			return (1);
		}
	}
	return (0);
}

int	ft_exit(t_commands *cmd, t_env_vars *vars)
{
	char				*temp;
	unsigned long long	test;

	if (!cmd->cmd[1])
		exit(vars->exit_code);
	if (exit_args(cmd))
		return (1);
	if (cmd->cmd[1])
		vars->exit_code = ft_atoi(cmd->cmd[1]);
	if (cmd->cmd[1][0] == '-')
	{
		temp = ft_strchr(cmd->cmd[1], '-') + 1;
		test = ft_atoi(temp);
	}
	printf("exit\n");
	if (!cmd->cmd[1])
		exit((unsigned char)vars->exit_code);
	if ((vars->exit_code > LLONG_MAX && (cmd->cmd[1][0] != '-')) \
	|| (test > LLONG_MAX \
	&& ft_strncmp("9223372036854775808", temp, 19) != 0))
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd->cmd[1]);
		vars->exit_code = 255;
	}
	exit((unsigned char)vars->exit_code);
}
