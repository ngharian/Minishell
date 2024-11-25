/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:11:10 by gdero             #+#    #+#             */
/*   Updated: 2024/11/15 17:43:49 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

char	*get_path_line(char **env, char *line)
{
	int		index;
	char	*path;

	index = -1;
	while (env[++index])
	{
		if (ft_strncmp(env[index], line, ft_strlen(line)) == 0)
		{
			path = ft_strchr(env[index], '/');
			return (path);
		}
	}
	return (NULL);
}

int	ft_pwd(char **cmd, t_env_vars *vars) //trouver exactement la longueur de la string du path (pour malloc le buffer et pour la size du getcwd)
{
	char	*path;

	if (cmd[1])
	{
		printf("minishell: pwd: Too many arguments\n");
		return (3);
	}
	path = get_path_line(vars->env, "PWD=");
	if (!path)
	{
		printf("minishell: pwd: could not find path ; where are you?!\n");
		return (3);
	}
	printf("%s\n", path);
	return (3);
}