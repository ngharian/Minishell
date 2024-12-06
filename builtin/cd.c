/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:10:44 by gdero             #+#    #+#             */
/*   Updated: 2024/12/06 15:30:00 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

//mode 0 == env ; mode 1 == export
static int	update_oldpwd(char ***var, char *oldpwd, int mode)
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
				return (1);
			(*var)[index] = oldpwd;
			return (0);
		}
	}
	return (0);
}

//to_find definit si env ou export
int	change_pwd(char ***var, char *line, char *to_find)
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
				return (1);
			if (ft_strncmp(to_find, "declare -x PWD=\"", \
			ft_strlen(to_find)) == 0)
				newpath = ft_strjoin(newpath, "\"");
			if (!newpath)
				return (1);
			(*var)[index] = newpath;
		}
	}
	if (update_oldpwd(&(*var), oldpwd, 0) || update_oldpwd(&(*var), oldpwd, 1))
		return (1);
	return (0);
}

//mode 0 == ~/ ; mode 1 == relative path
int	add_to_path(char **newpath, char *line, char *home, int mode)
{
	char	*path;

	if (mode == 0)
		path = line + 1;
	if (mode == 1)
	{
		path = "/";
		if (line[ft_strlen(line) - 1] == '/')
			line[ft_strlen(line) - 1] = '\0';
		path = ft_strjoin(path, line);
		if (!path)
			return (1);
	}
	path = ft_strjoin(home, path);
	if (!path)
		return (1);
	*newpath = path;
	return (0);
}

static int	type_of_cd(char *line)
{
	if (line[0] == '~' && line[1] == '/')
	{
		if (line[2] == '.' && line[3] == '.' && !line[4])
			return (7);
		return (1);
	}
	else if (line[0] == '/' && (!line[1] || \
	(line[1] == '.' && line[2] == '\0') || \
	(line[1] == '.' && line[2] == '.' && !line[3])))
		return (2);
	else if ((line[0] == '.' && line[1] == '/') || ft_isalnum(line[0]))
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
	char	*home;

	home = get_path_line(vars->env, "HOME=", 1) + 1;
	if (!home)
		return (-1);
	if (!cmd->cmd[1] || (cmd->cmd[1][0] == '~' && cmd->cmd[1][1] == '\0'))
	{
		chdir(home);
		if (change_pwd(&vars->env, home, "PWD=") || \
		change_pwd(&vars->exp, home, "declare -x PWD=\""))
			return (-1);
		return (2);
	}
	mode = type_of_cd(cmd->cmd[1]);
	if (mode < 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", cmd->cmd[1]);
		return (2);
	}
	if (mode == 1 || mode == 6)
		return (change_directory_1_6(vars, mode, cmd->cmd[1], home));
	else
		return (change_directory_else(vars, mode, cmd->cmd[1], home));
}
