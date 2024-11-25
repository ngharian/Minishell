/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:21:58 by gdero             #+#    #+#             */
/*   Updated: 2024/11/19 14:50:47 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins(t_commands *cmd, t_env_vars *vars)
{
	int	    index;
	int	    condition_met;
    char    *lower_cmd;
    char *const ls = "ls"; //debilos, surtout pour pas oublier

	condition_met = 0;
	index = -1;
    lower_cmd = ft_strdup(cmd->cmd[0]); //il faut.
    if (!lower_cmd)
        return (-1); //??
	while (cmd->cmd[0][++index])
		lower_cmd[index] = ft_tolower(cmd->cmd[0][index]);
    if (ft_strncmp(lower_cmd, "/bin/ls", 7) == 0) //ligne debile, 1er check de l'eval
        execve("/bin/ls", &ls, vars->env);
	if (ft_strncmp(lower_cmd, "echo", 4) == 0)
        condition_met = ft_echo(cmd->cmd);
    if (ft_strncmp(lower_cmd, "cd", 2) == 0)
        condition_met = ft_cd(cmd, vars);
    if (ft_strncmp(lower_cmd, "pwd", 3) == 0)
        condition_met = ft_pwd(cmd->cmd, vars);
    if (ft_strncmp(lower_cmd, "export", 6) == 0)
        condition_met = ft_export(cmd->cmd, vars);
    if (ft_strncmp(lower_cmd, "unset", 5) == 0)
		condition_met = ft_unset(cmd->cmd, vars);
    if (ft_strncmp(lower_cmd, "env", 3) == 0)
        condition_met = ft_env(cmd->cmd, vars, 0);
    if (ft_strncmp(lower_cmd, "exit", 4) == 0) //ne fonctionne QUE s'il n'y a pas de pipe
        condition_met = ft_exit(cmd);
	return (free(lower_cmd), condition_met);
}
