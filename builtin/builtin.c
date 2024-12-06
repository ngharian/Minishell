/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:21:58 by gdero             #+#    #+#             */
/*   Updated: 2024/12/05 15:42:30 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins(t_commands *cmd, t_env_vars *vars)
{
	int	    index;
	int	    condition_met;
    char    *lower_cmd;

	condition_met = 0;
	index = -1;
    lower_cmd = ft_strdup(cmd->cmd[0]);
	if (!lower_cmd)
		return (-1);
	while (lower_cmd && cmd->cmd[0][++index])
		lower_cmd[index] = ft_tolower(cmd->cmd[0][index]);
	if (ft_strncmp(lower_cmd, "echo", 4) == 0)
        condition_met = ft_echo(cmd->cmd);
    else if (ft_strncmp(lower_cmd, "cd", 2) == 0)
        condition_met = ft_cd(cmd, vars);
    else if (ft_strncmp(lower_cmd, "pwd", 3) == 0)
        condition_met = ft_pwd(cmd->cmd, vars);
    else if (ft_strncmp(lower_cmd, "export", 6) == 0)
        condition_met = ft_export(cmd->cmd, vars);
    else if (ft_strncmp(lower_cmd, "unset", 5) == 0)
		condition_met = ft_unset(cmd->cmd, vars);
    else if (ft_strncmp(lower_cmd, "env", 3) == 0)
        condition_met = ft_env(cmd->cmd, vars, 0);
    else if (ft_strncmp(lower_cmd, "exit", 4) == 0)
        condition_met = ft_exit(cmd, vars);
    //exit_code;
	return (free(lower_cmd), condition_met);
}
