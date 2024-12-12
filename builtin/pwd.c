/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:11:10 by gdero             #+#    #+#             */
/*   Updated: 2024/12/12 20:37:05 by gdero            ###   ########.fr       */
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

	(void)cmd; //ATTENTION
	path = get_path_line(vars->env, "PWD=", 0);
	if (!path)
	{
		print_exit_error("PWD not set", NULL, -1, "pwd: ");
		return (1);
	}
	printf("%s\n", path);
	return (0);
}
