/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:11:10 by gdero             #+#    #+#             */
/*   Updated: 2024/11/26 16:48:59 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

char	*get_path_line(char **env, char *line, int mode)
{
	int		index;
	char	*path;

	index = -1;
	while (env[++index])
	{
		if (ft_strncmp(env[index], line, ft_strlen(line)) == 0)
		{
			if (mode == 0)
				path = ft_strchr(env[index], '/');
			else
				path = ft_strchr(env[index], '=');
			return (path);
		}
	}
	return (NULL);
}

int	ft_pwd(char **cmd, t_env_vars *vars)
{
	char	*path;

	if (cmd[1])
	{
		printf("minishell: pwd: Too many arguments\n");
		return (3);
	}
	path = get_path_line(vars->env, "PWD=", 0);
	if (!path)
	{
		printf("minishell: pwd: could not find path ; where are you?!\n");
		return (3);
	}
	printf("%s\n", path);
	return (3);
}
