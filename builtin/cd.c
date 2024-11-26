/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:10:44 by gdero             #+#    #+#             */
/*   Updated: 2024/11/26 19:21:43 by gdero            ###   ########.fr       */
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
static int	change_pwd(char ***var, char *line, char *to_find)
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
static int	add_to_path(char **newpath, char *line, char *home, int mode)
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

static void	change_to_parent(t_env_vars *vars, char **path)
{
	int		index;
	int		str_index;
	char	*temp;

	index = -1;
	temp = NULL;
	while (vars->env[++index])
	{
		if (ft_strncmp(vars->env[index], "PWD=", 4) == 0)
		{
			temp = ft_strchr(vars->env[index], '/');
			break ;
		}
	}
	str_index = ft_strlen(temp);
	while (temp[--str_index])
	{
		if (temp[str_index] == '/')
		{
			temp[str_index] = '\0';
			break ;
		}
	}
	*path = temp;
}

static char *user_path(char **var, char *line, char *home)
{
	int		index;
	char	*temp;
	char	*lower_line;

	index = -1;
	line = line + 1;
	temp = NULL;
	lower_line = ft_strdup(line); //Faut le faire sinon rendra la ligne en lower
	if (!lower_line)
		return (NULL);
	while (line[++index])
		lower_line[index] = ft_tolower(line[index]);
	index = -1;
	while (var[++index])
	{
		if (ft_strncmp(var[index], "USER=", 5) == 0)
		{
			temp = ft_strchr(var[index], '=') + 1;
			break ;
		}
	}
	index = -1;
	while (temp[++index])
		temp[index] = ft_tolower(temp[index]);
	if (ft_strncmp(lower_line, temp, ft_strlen(temp)) == 0)
		return (free(lower_line), home);
	else
		return (free(lower_line), line - 1);
}

static int	change_directory(t_env_vars *vars, int mode, char *line, char *home)
{
	char	*newpath;
	bool	malloked;

	malloked = false;
	if (mode == 1)
	{
		if (line[2] == '.')
			line[2] = '\0';
		if (add_to_path(&newpath, line, home, 0))
			return (1);
		malloked = true;
	}
	else if (mode == 2)
		newpath = "/";
	else if (mode == 4)
		change_to_parent(vars, &newpath);
	else if (mode == 6)
	{
		if (line[0] == '.')
			line = ft_strchr(line, '/') + 1;
		home = get_path_line(vars->env, "PWD=", 0);
		if (add_to_path(&newpath, line, home, 1)) // ft_strlcat ?
			return (1);
		malloked = true;
	}
	else if (mode == 7)
		newpath = "/Users";
	else if (mode == 8)
		newpath = user_path(vars->env, line, home);
	else if (mode == 9)
		newpath = get_path_line(vars->env, "OLDPWD=", 0);
	else
		return (2);
	line = newpath;
	if (chdir(newpath) == -1)
	{
		if (access(newpath, F_OK) == 0)
		{
			printf("minishell: cd: %s: Not a directory\n", ft_strrchr(line, '/') + 1);
			return (2);
		}
		printf("minishell: cd: %s: No such file or directory\n", line);
		return (2);
	}
	if (line[ft_strlen(line) - 1] == '/' && mode != 2)
		line[ft_strlen(line) - 1] = '\0';
	if (change_pwd(&vars->env, line, "PWD=") || change_pwd(&vars->exp, line, "declare -x PWD=\""))
		return (-1);
	if (malloked == true)
		free(newpath);
	return (2);
}

static int	type_of_cd(char *line)
{
	if (line[0] == '~' && line[1] == '/')
	{
		if (line[2] == '.' && line[3] == '.' && !line[4])
			return (7);
		return (1);
	}
	else if (line[0] == '/' && (!line[1] || (line[1] == '.' && line[1] == '\0') || (line[1] == '.' && line[1] == '.' && !line[2])))
		return (2);
	else if ((line[0] == '.' && line[1] == '/') || ft_isalnum(line[0]))
		return (6);
	else if (line[0] == '.' && line[1] == '.') //!! si dossier supprime
		return (4);
	/*else if (ft_isalnum(line[0]))
		return (6);*/
	else if (line[0] == '~' && ft_isalpha(line[1]))
		return (8);
	else if (line[0] == '-' && !line[1]) // !!! si dossier supprime
		return (9);
	return (-1);
}

int	ft_cd(t_commands *cmd, t_env_vars *vars) //prend juste le 1er arg, s'en fout si plus
{
	int		index;
	int		mode;
	char	*home;

	index = 0;
	home = get_path_line(vars->env, "HOME=", 1) + 1;
	if (!home)
		return (-1);
	if (!cmd->cmd[1] || (cmd->cmd[1][0] == '~' && cmd->cmd[1][1] == '\0'))
	{
		chdir(home);
		if (change_pwd(&vars->env, home, "PWD=") || change_pwd(&vars->exp, home, "declare -x PWD=\""))
			return (-1);
		return (2);
	}
	mode = type_of_cd(cmd->cmd[1]);
	if (mode < 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", cmd->cmd[1]);
		return (2);
	}
	return (change_directory(vars, mode, cmd->cmd[1], home));
}
