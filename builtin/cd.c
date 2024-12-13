/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:40:11 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/13 14:10:04 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	compare_string_and_join(char **string, \
char *to_find, char **oldpwd, char *line)
{
	char	*temp;
	char	*newpath;

	if (ft_strncmp((*string), to_find, ft_strlen(to_find)) == 0)
	{
		*oldpwd = ft_strdup(ft_strchr((*string), '=') + 1);
		if (!(*oldpwd))
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		free((*string));
		newpath = ft_strjoin(to_find, line);
		if (!newpath)
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		if (ft_strncmp(to_find, "declare -x PWD=\"", \
		ft_strlen(to_find)) == 0)
		{
			temp = newpath;
			newpath = ft_strjoin(temp, "\"");
			free(temp);
		}
		if (!newpath)
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		(*string) = newpath;
	}
}

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

	path = cmd->cmd[1];
	if (!cmd->cmd[1])
	{
		path = get_path_line(vars->env, "HOME=", 0);
		if (!path)
		{
			print_exit_error("HOME not set", NULL, -1, "cd: ");
			return (1);
		}
	}
	else if (minus_case(cmd, &path, vars))
		return (1);
	if (chdir(path) != 0)
	{
		print_exit_error(strerror(errno), path, -1, "cd: ");
		return (1);
	}
	return (0);
}
