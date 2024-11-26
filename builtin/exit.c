/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:12:28 by gdero             #+#    #+#             */
/*   Updated: 2024/11/26 16:44:55 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static int	exit_args(t_commands *cmd, t_env_vars *vars)
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
		if (cmd->cmd[2])
		{
			printf("exit\nminishell: exit: too many arguments\n");
			vars->exit_code = 1;
			return (1);
		}
	}
	return (0);
}

int	ft_exit(t_commands *cmd, t_env_vars *vars)
{
	if (cmd->previous != NULL || cmd->next != NULL)
		return (7);
	if (exit_args(cmd, vars))
		return (7);
	if (cmd->cmd[1])
		vars->exit_code = ft_atoi(cmd->cmd[1]);
	printf("exit\n");
	if ((vars->exit_code > 9223372036854775807 && (cmd->cmd[1][0] != '-')) \
	|| vars->exit_code <= LONG_LONG_MAX)
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd->cmd[1]);
		vars->exit_code = 255;
	}
	exit((unsigned char)vars->exit_code);
}
