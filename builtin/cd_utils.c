/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:57:57 by gdero             #+#    #+#             */
/*   Updated: 2024/12/09 19:11:33 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	change_to_parent(t_env_vars *vars, char **path)
{
	int		str_index;
	char	*temp;

	temp = get_path_line(vars->env, "PWD=", 0);
	if (!temp)
		return (print_exit_error("PWD not set", NULL, -1, "cd: "));
	str_index = ft_strlen(temp);
	while (temp[--str_index])
	{
		if (temp[str_index] == '/')
		{
			temp[str_index] = '\0';
			break ;
		}
	}
	if (temp[0] == '\0')
		*path = "/";
	else
		*path = temp;
}

static char	*user_path(char **var, char *line, char *home, int index)
{
	char	*temp;
	char	*lower_line;

	temp = NULL;
	lower_line = ft_strdup(line);
	if (!lower_line)
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
	while (line[++index])
		lower_line[index] = ft_tolower(line[index]);
	index = -1;
	temp = get_path_line(var, "USER=", 1);
	if (!temp)
	{
		print_exit_error("USER not set", NULL, -1, "cd: ");
		return (free(lower_line), NULL);
	}
	temp++;
	index = -1;
	while (temp[++index])
		temp[index] = ft_tolower(temp[index]);
	if (ft_strncmp(lower_line, temp, ft_strlen(temp)) == 0)
		return (free(lower_line), home);
	else
		return (free(lower_line), line - 1);
}

void	change_dir(t_env_vars *vars, int mode, char *line, char *newpath)
{
	if (chdir(newpath) == -1)
	{
		if (mode == 4)
		{
			chdir(get_path_line(vars->env, "HOME=", 1) + 1);
			change_pwd(&vars->env, \
			get_path_line(vars->env, "HOME=", 1) + 1, "PWD=");
			change_pwd(&vars->exp, \
			get_path_line(vars->env, "HOME=", 1) + 1, "declare -x PWD=\"");
			return ;
		}
		if (access(newpath, F_OK) == 0)
			return (print_exit_error("Not a directory", \
			ft_strrchr(line, '/') + 1, -1, "cd: "));
		return (print_exit_error("No such file or directory", \
		line, -1, "cd: "));
	}
	if (line[ft_strlen(line) - 1] == '/' && mode != 2 && mode != 4)
		line[ft_strlen(line) - 1] = '\0';
	if (!get_path_line(vars->env, "PWD=", 1))
		return (print_exit_error("PWD not set", NULL, -1, "cd: "));
	change_pwd(&vars->env, line, "PWD=");
	change_pwd(&vars->exp, line, "declare -x PWD=\"");
}

int	change_directory_1_6(t_env_vars *vars, int mode, char *line, char *home)
{
	char	*newpath;

	if (mode == 1)
	{
		if (line[2] == '.' && !line[3])
			line[2] = '\0';
		add_to_path(&newpath, line, home, 0);
	}
	if (mode == 6)
	{
		if (line[0] == '.')
			line = ft_strchr(line, '/') + 1;
		home = get_path_line(vars->env, "PWD=", 0);
		if (!home)
			return (print_exit_error("PWD not set", NULL, -1, "cd: "), 2);
		if (!home[1])
			home++;
		add_to_path(&newpath, line, home, 1);
	}
	line = newpath;
	change_dir(vars, mode, line, newpath);
	free(newpath);
	return (2);
}

int	change_directory_else(t_env_vars *vars, int mode, char *line, char *home)
{
	char	*newpath;

	if (mode == 2)
		newpath = "/";
	else if (mode == 4)
		change_to_parent(vars, &newpath);
	else if (mode == 7)
		newpath = "/Users";
	else if (mode == 8)
		newpath = user_path(vars->env, line + 1, home, -1);
	else if (mode == 9)
	{
		newpath = get_path_line(vars->env, "OLDPWD=", 0);
		if (!newpath)
			print_exit_error("OLDPWD not set", NULL, -1, "cd: ");
	}
	else
		return (2);
	if (!newpath)
		return (2);
	line = newpath;
	change_dir(vars, mode, line, newpath);
	return (2);
}
