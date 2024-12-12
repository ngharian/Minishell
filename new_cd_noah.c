/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cd_noah.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:40:11 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/12 17:40:27 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	minus_case(t_commands *cmd, char **path, t_env_vars *vars)
{
	if (cmd->cmd[1][0] == '-')
	{
		if (cmd->cmd[1][1] != '\0')
		{
			print_exit_error("invalid option", "-", -1, "cd: ");
			return (1);
		}
		*path = get_path_line(vars->env, "OLDPWD=", 0);
		if (!(*path))
		{
			print_exit_error("OLDPWD not set", NULL, -1, "cd: ");
			return (1);
		}
	}
	return (0);
}

int	ft_cd(t_commands *cmd, t_env_vars *vars)
{
	char	*path;

	if (!cmd->cmd[1])
	{
		path = get_path_line(vars->env, "HOME=", 0);
		if (!path)
		{
			print_exit_error("HOME not set", NULL, -1, "cd: ");
			return (1);
		}
	}
	path = cmd->cmd[1];
	if (minus_case(cmd, &path, vars))
		return (1);
	if (chdir(path) != 0)
	{
		print_exit_error(strerror(errno), path, -1, "cd: ");
		return (1);
	}
	return (0);
}
