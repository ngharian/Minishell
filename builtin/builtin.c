/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:21:58 by gdero             #+#    #+#             */
/*   Updated: 2024/12/13 14:03:29 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins(t_commands *cmd, t_env_vars *vars, int index)
{
	int		condition_met;
	char	*lower_cmd;

	condition_met = -1;
	lower_cmd = ft_strdup(cmd->cmd[0]);
	if (!lower_cmd)
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
	while (lower_cmd && cmd->cmd[0][++index])
		lower_cmd[index] = ft_tolower(cmd->cmd[0][index]);
	if (ft_strcmp(lower_cmd, "echo") == 0)
		condition_met = ft_echo(cmd->cmd, vars, 1);
	else if (ft_strcmp(lower_cmd, "cd") == 0)
		condition_met = ft_cd(cmd, vars);
	else if (ft_strcmp(lower_cmd, "pwd") == 0)
		condition_met = ft_pwd(vars);
	else if (ft_strcmp(lower_cmd, "export") == 0)
		condition_met = ft_export(cmd->cmd, vars);
	else if (ft_strcmp(lower_cmd, "unset") == 0)
		condition_met = ft_unset(cmd->cmd, vars);
	else if (ft_strcmp(lower_cmd, "env") == 0)
		condition_met = ft_env(cmd->cmd, vars, 0);
	else if (ft_strcmp(lower_cmd, "exit") == 0)
		condition_met = ft_exit(cmd, vars);
	return (free(lower_cmd), condition_met);
}
