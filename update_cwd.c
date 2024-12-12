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
	//add_to_var(oldpwd, mode, t_env_vars **vars, int *index_mode);
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


static char **set_split(char *to_write)
{
    char    **oldpwd;

    oldpwd = malloc(sizeof(char *) * 3);
    if (!oldpwd)
        print_exit_error("Malloc error", NULL, 1, NULL);
    oldpwd[2] = NULL;
    //if (split[1])
      //  free(split[1]);
    oldpwd[1] = ft_strdup(to_write);
    if (!oldpwd[1])
        print_exit_error("Malloc error", NULL, 1, NULL);
    return (oldpwd);

}

void update_env(t_env_vars **env, char *new_cmd, int mode, int is_old_there)
{
    char    **oldpwd;

    oldpwd = NULL;
    if (get_path_line((*env)->env, "OLDPWD=", 1) == NULL)
        is_old_there = 1;
    else
        oldpwd = set_split("OLDPWD=");
    if (mode == 0)
    {
        if (is_old_there == 1)
            ft_unset(oldpwd, *env);
        oldpwd = set_split(new_cmd);
        ft_export(oldpwd, *env);
    }
    if (mode == 1)
    {
        if (is_old_there == 0)
            ft_export(oldpwd, *env);
        change_pwd(&(*env)->env, new_cmd, "PWD=");
        change_pwd(&(*env)->exp, new_cmd, "declare -x PWD=");
    }
    free(oldpwd[1]);
    free(oldpwd);
}

void    update_cwd(t_env_vars **env, int mode)
{
    char    buffer[1024];
    char    *current_cwd;
    char    *new_cwd;

    if (mode == 1)
    {
        new_cwd = (*env)->mini_root;
        if (chdir(new_cwd) != 0)
            print_exit_error("unable to go to minishell root", NULL, 1, NULL);
    }
    new_cwd = getcwd(buffer, sizeof(buffer));
    if (!new_cwd)
    {
        print_exit_error("returning to minishell root", "getcwd() error", -1, NULL);
        update_cwd(env, 1);
        return ;
    }
    current_cwd = get_path_line((*env)->env, "PWD=", 1);
    if (!current_cwd)
        return (update_env(env, new_cwd, 0, 0)); //export join("PWD=", "new_cwd")
    ++current_cwd;
    if (ft_strcmp(new_cwd, current_cwd) == 0)
        return ;
    else
        update_env(env, new_cwd, 1, 0);
}
