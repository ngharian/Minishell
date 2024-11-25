/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newcd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:10:44 by gdero             #+#    #+#             */
/*   Updated: 2024/11/16 17:18:15 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static int	change_pwd(t_env_vars **vars, char *line)
{
	int		index;
	char	*newpath;

	index = -1;
	newpath = NULL;
	while ((*vars)->env[++index])
	{
		if (ft_strncmp((*vars)->env[index], "PWD=", 4) == 0)
		{
			free((*vars)->env[index]);
			newpath = ft_strjoin("PWD=", line);
			if (!newpath)
				return (1);
			(*vars)->env[index] = newpath;
			break ;
		}
	}
	return (0);
}

static int	add_to_path(t_env_vars *vars, char **newpath, char *line)
{
	char	*path;

	path = line + 1;
	path = ft_strjoin(vars->home, path);
	if (!path)
		return (1);
	*newpath = path;
	return (0);
}
static int	change_directory(t_env_vars *vars, int mode, char *line)
{
	char	*newpath;

	if (mode == 0)
	{
		chdir(vars->home);//peut foirer
		if (change_pwd(&vars, vars->home))
			return (-1);	
	}
	if (mode == 1)
	{
		if (add_to_path(vars, &newpath, line))
			return (1);
		chdir(newpath);
		if (change_pwd(&vars, newpath))
			return (-1);
	}
	return (2);
}
static int	type_of_cd(char *line)
{
	if (line[0] == '~')
		return (1);
	return (0);
}
//mode 1 == .. ; mode 2 == ~ (seul == cd simple); mode 3 == directory ??? !!! "not a directory"
//cd ~/.. va plus loin que HOME (Users)
//cd / va plus loin que Users
int	ft_cd(t_commands *cmd, t_env_vars *vars) //prend juste le 1er arg, s'en fout si plus
{
	int		index;
	int		mode;
	//char	*temp;

	index = 0;
	if (!cmd->cmd[1] || (cmd->cmd[1][0] == '~' && cmd->cmd[1][1] == '\0'))
		return (change_directory(vars, 0, vars->home));
	mode = type_of_cd(cmd->cmd[1]);
	return (change_directory(vars, mode, cmd->cmd[1]));
}