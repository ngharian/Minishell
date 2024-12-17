/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:21:58 by gdero             #+#    #+#             */
/*   Updated: 2024/12/17 17:52:54 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins(t_commands *cmd, t_env_vars *vars)
{
	int		condition_met;

	condition_met = -1;
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		condition_met = ft_echo(cmd->cmd, 1);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		condition_met = ft_cd(cmd, vars);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		condition_met = ft_pwd(vars);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		condition_met = ft_export(cmd->cmd, vars);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		condition_met = ft_unset(cmd->cmd, vars);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		condition_met = ft_env(cmd->cmd, vars, 0);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		condition_met = ft_exit(cmd, vars);
	return (condition_met);
}
