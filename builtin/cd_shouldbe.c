/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_shouldbe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:10:44 by gdero             #+#    #+#             */
/*   Updated: 2024/12/11 19:58:20 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

//mode 0 == env ; mode 1 == export
static void	update_oldpwd(char ***var, char *oldpwd, int mode)
{
	int		index;
	char	*to_find;

	index = -1;
	if (mode == 0)
		to_find = "OLDPWD=";
	else
		to_find = "declare -x OLDPWD=";
	while ((*var)[++index])
	{
		if (ft_strncmp((*var)[index], to_find, ft_strlen(to_find)) == 0)
		{
			free((*var)[index]);
			oldpwd = ft_strjoin(to_find, oldpwd);
			if (!oldpwd)
				print_exit_error("Malloc error!\n", NULL, 1, NULL);
			(*var)[index] = oldpwd;
			return ;
		}
	}
}

//to_find definit si env ou export
void	change_pwd(char ***var, char *line, char *to_find)
{
	int		index;
	char	*newpath;
	char	*oldpwd;

	index = -1;
	while ((*var)[++index])
	{
		if (ft_strncmp((*var)[index], to_find, ft_strlen(to_find)) == 0)
		{
			oldpwd = ft_strchr((*var)[index], '=') + 1;
			free((*var)[index]);
			newpath = ft_strjoin(to_find, line);
			if (!newpath)
				print_exit_error("Malloc error!\n", NULL, 1, NULL);
			if (ft_strncmp(to_find, "declare -x PWD=\"", \
			ft_strlen(to_find)) == 0)
				newpath = ft_strjoin(newpath, "\"");
			if (!newpath)
				print_exit_error("Malloc error!\n", NULL, 1, NULL);
			(*var)[index] = newpath;
		}
	}
	update_oldpwd(&(*var), oldpwd, 0);
	update_oldpwd(&(*var), oldpwd, 1);
}

//mode 0 == ~/ ; mode 1 == relative path
void	add_to_path(char **newpath, char *line, char *home, int mode)
{
	char	*path;
	char	*finalpath;
	bool	malloked;

	malloked = false;
	if (mode == 0)
		path = line + 1;
	if (mode == 1)
	{
		path = "/";
		path = ft_strjoin(path, line);
		if (!path)
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		malloked = true;
	}
	finalpath = ft_strjoin(home, path);
	if (!finalpath)
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
	if (malloked == true)
		free(path);
	*newpath = finalpath;
}

static int	type_of_cd(char *line)
{
	if (ft_isalnum(line[0]))
		return (6);
	else if (line[0] == '.' && line[1] == '.')
		return (4);
	else if (line[0] == '~' && ft_isalpha(line[1]))
		return (8);
	else if (line[0] == '-' && !line[1])
		return (9);
	else if (line[0] == '.' && !line[1])
		return (10);
	return (-1);
}

int	ft_cd(t_commands *cmd, t_env_vars *vars)
{
	int		mode;
	int		index;
	char	*home;
	char	**cd_split;
	char	*trimmed;
	char	*pwd;
	bool	error;

	index = -1;
	error = false;
	home = get_path_line(vars->env, "HOME=", 1);
	pwd = get_path_line(vars->env, "PWD=", 0);
	if (!home)
	{
		print_exit_error("HOME not set", NULL, -1, "cd: ");
		return (2);
	}
	home++;
	if (!cmd->cmd[1] || (cmd->cmd[1][0] == '~' && cmd->cmd[1][1] == '\0'))
	{
		change_dir(vars, 0, home, home, &error);
		return (1);
	}
	if (cmd->cmd[1])
	{
		if (cmd->cmd[1][0] == '/')
			change_directory_else(vars, 2, "/", home, &error);
		trimmed = ft_strtrim(cmd->cmd[1], "/ ");
		cd_split = ft_split(trimmed, '/');
		while (cd_split[++index])
		{
			mode = type_of_cd(cd_split[index]);
			if (mode == 6)
				change_directory_6(vars, cd_split[index], home, &error);
			else
				change_directory_else(vars, mode, cd_split[index], home, &error);
		}
		free(trimmed);
		free_split(cd_split);
	}
	if (error == true)
		change_dir(vars, 0, pwd, home, false);
	return (1);
	/*if (mode < 0)
	{
		print_exit_error("No such file or directory", \
		cmd->cmd[1], -1, "cd: ");
		return (2);
	}*/
}
