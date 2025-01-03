/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:37:16 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/13 15:12:27 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(char ***var, char *oldpwd, int mode)
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

void	change_pwd(char ***var, char *line, char *to_find)
{
	int		index;
	char	*oldpwd;

	index = -1;
	while ((*var)[++index])
		compare_string_and_join(&(*var)[index], to_find, &oldpwd, line);
	update_oldpwd(&(*var), oldpwd, 0);
	update_oldpwd(&(*var), oldpwd, 1);
	free(oldpwd);
}

static char	**set_split(char *to_write, char **splitted)
{
	char	**oldpwd;

	oldpwd = malloc(sizeof(char *) * 3);
	if (!oldpwd || !to_write)
		print_exit_error("Malloc error", NULL, 1, NULL);
	if (splitted != NULL)
	{
		if (splitted[1])
			free(splitted[1]);
	}
	oldpwd[2] = NULL;
	oldpwd[1] = ft_strdup(to_write);
	if (!oldpwd[1])
		print_exit_error("Malloc error", NULL, 1, NULL);
	return (oldpwd);
}

void	update_env(t_env_vars **env, char *new_cmd, int mode, int is_old_there)
{
	char	**oldpwd;

	oldpwd = set_split("OLDPWD", NULL);
	if (get_path_line((*env)->env, "OLDPWD=", 1) != NULL)
		is_old_there = 1;
	else
		oldpwd = set_split("OLDPWD=", oldpwd);
	if (mode == 0)
	{
		if (is_old_there == 1)
			ft_unset(oldpwd, *env);
		new_cmd = ft_strjoin("PWD=", new_cmd);
		oldpwd = set_split(new_cmd, oldpwd);
		ft_export(oldpwd, *env);
		free(new_cmd);
	}
	if (mode == 1)
	{
		if (is_old_there == 0)
			ft_export(oldpwd, *env);
		change_pwd(&(*env)->env, new_cmd, "PWD=");
		change_pwd(&(*env)->exp, new_cmd, "declare -x PWD=\"");
	}
	free(oldpwd[1]);
	free(oldpwd);
}

void	update_cwd(t_env_vars **env, int mode)
{
	char	buffer[1024];
	char	*current_cwd;
	char	*new_cwd;

	if (mode == 1)
	{
		new_cwd = (*env)->mini_root;
		if (chdir(new_cwd) != 0)
			print_exit_error("unable to go to minishell root", NULL, 1, NULL);
	}
	new_cwd = getcwd(buffer, sizeof(buffer));
	if (!new_cwd)
	{
		print_exit_error("returning to minishell root", \
						"getcwd() error", -1, NULL);
		update_cwd(env, 1);
		return ;
	}
	current_cwd = get_path_line((*env)->env, "PWD=", 1);
	if (!current_cwd)
		return (update_env(env, new_cwd, 0, 0));
	++current_cwd;
	if (ft_strcmp(new_cwd, current_cwd) == 0)
		return ;
	update_env(env, new_cwd, 1, 0);
}
