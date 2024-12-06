/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:13:12 by gdero             #+#    #+#             */
/*   Updated: 2024/12/06 16:26:52 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static int	append_or_not(int mode, char **new_env, char *str, int str_index)
{
	int	str_index2;

	if (mode == 7 || mode == 8)
	{
		(*new_env) = malloc((ft_strlen(str)) * sizeof(char));
		if (!(*new_env))
			return (1);
		(*new_env)[ft_strlen(str) - 1] = '\0';
		while (str[++str_index] != '+')
			(*new_env)[str_index] = str[str_index];
		str_index2 = str_index;
		while (str[++str_index])
			(*new_env)[str_index2++] = str[str_index];
	}
	else
	{
		(*new_env) = malloc((ft_strlen(str) + 1) * sizeof(char));
		if (!(*new_env))
			return (1);
		(*new_env)[ft_strlen(str)] = '\0';
		(*new_env) = ft_strdup(str);
		if (!(*new_env))
			return (1);
	}
	return (0);
}

static int	add_line_to_env(char ***env, char ***new_env, char *str, int mode)
{
	int	index;

	index = 0;
	while ((*env)[index])
		index++;
	(*new_env) = malloc((index + 2) * sizeof(char *));
	if (!new_env)
		return (1);
	(*new_env)[index + 1] = NULL;
	index = -1;
	while ((*env)[++index])
	{
		(*new_env)[index] = ft_strdup((*env)[index]);
		if (!(*new_env)[index])
			return (1);
	}
	if (append_or_not(mode, &(*new_env)[index], str, -1))
		return (1);
	free_split(*env);
	(*env) = (*new_env);
	return (0);
}

static int	the_sixth_mode(char **oldstring, char *to_append, char **newstring)
{
	int	index;
	int	index2;

	index = 0;
	while (to_append[index] != '=')
		index++;
	index2 = index;
	while (to_append[index2])
		index2++;
	(*newstring) = malloc((index2 - index) * sizeof(char));
	if (!(*newstring))
		return (1);
	(*newstring)[index2 - index - 1] = '\0';
	index2 = -1;
	while (to_append[++index])
		(*newstring)[++index2] = to_append[index];
	if (cmd_without_quotes(oldstring))
		return (1);
	(*newstring) = ft_strjoin(*oldstring, (*newstring));
	if (!(*newstring))
		return (1);
	return (0);
}

static int	append_var(char **oldstring, char *to_append, int mode)
{
	int		index;
	int		index2;
	char 	*newstring;

	index = -1;
	if (mode == 6)
	{
		if (the_sixth_mode(oldstring, to_append, &newstring))
			return (1);
	}
	else
	{
		newstring = malloc((ft_strlen(to_append)) * sizeof(char));
		if (!newstring)
			return (1);
		newstring[ft_strlen(to_append) - 1] = '\0';
		while (to_append[++index] != '+')
			newstring[index] = to_append[index];
		index2 = index;
		while (to_append[++index])
			newstring[index2++] = to_append[index];
	}
	free(*oldstring);
	*oldstring = newstring;
	return (0);
}

static int	add_to_exp(char *str, int mode, t_env_vars **vars, int *index_mode)
{
	char	**new_exp;

	new_exp = NULL;
	if (mode == 2 || mode == 5)
	{
		free((*vars)->exp[*index_mode]);
		(*vars)->exp[*index_mode] = ft_strdup(str);
		if (!(*vars)->exp[*index_mode])
			return (1);
		return (0);
	}
	if (mode == 6 || mode == 7)
	{
		if (append_var(&(*vars)->exp[*index_mode], str, mode))
			return (1);
		return (0);
	}
	if (add_line_to_env(&(*vars)->exp, &new_exp, str, mode))
		return (1);
	return (0);
}

static int	new_index_mode(char *str, char **env)
{
	int		index;
	int		str_index;
	char 	*temp;

	index = -1;
	str_index = 0;
	while (str[str_index] != '+' \
	&& str[str_index] != '=' && str[str_index] != '\0')
		str_index++;
	while (env[++index])
	{
		temp = env[index];
		if (ft_strncmp(str, temp, str_index) == 0 && temp[str_index] == '=')
			return (index);
	}
	return (0);
}

static int	add_to_env(char *str, int mode, t_env_vars **vars)
{
	int		index;
	char	**new_env;

	new_env = NULL;
	index = new_index_mode(str, (*vars)->env);
	if (mode == 4 || mode == 9)
		return (0);
	if (mode == 2)
	{
		free((*vars)->env[index]);
		(*vars)->env[index] = ft_strdup(str);
		if (!(*vars)->env[index])
			return (1);
		return (0);
	}
	if (mode == 6)
	{
		if (append_var(&(*vars)->env[index], str, mode))
			return (1);
		return (0);
	}
	if (add_line_to_env(&(*vars)->env, &new_env, str, mode))
		return (1);
	return (0);
}

static int	add_to_var(char *str, int mode, t_env_vars **vars, int *index_mode)
{
	int	index;

	index = 0;
	if (mode == 1)
		return (0);
	if (add_to_exp(str, mode, vars, index_mode))
		return (1);
	if (add_to_env(str, mode, vars))
		return (1);
	while ((*vars)->exp[index])
		index++;
	index--;
	if (mode == 3 || mode == 8)
		(*vars)->exp[index] = add_char((*vars)->exp[index], mode);
	if (mode == 4)
		(*vars)->exp[index] = ft_strjoin("declare -x ", (*vars)->exp[index]);
	if (!(*vars)->exp[index])
		return (1);
	if (mode == 2 || mode == 5 || mode == 6 || mode == 7)
	{
		(*vars)->exp[*index_mode] = add_char((*vars)->exp[*index_mode], mode);
		if (!(*vars)->exp[*index_mode])
			return (1);
	}
	return (make_order(*vars, index));
}

static int	ft_must_export(bool must_append, char *cmd, int index_str, t_env_vars *vars)
{
	int	mode;
	int	index_mode;

	if (must_append == true) //a trier
		mode = already_exists(cmd, &vars, &index_mode, index_str);
	else
		mode = already_exists(cmd, &vars, &index_mode, index_str);
	if (add_to_var(cmd, mode, &vars, &index_mode))
		return (-1);
	return (0);
}

static void	check_export_args(char *cmd, bool *must_export, bool *must_append, int *index_str)
{
	if (cmd[0] == '=') //new
	{
		printf("minishell: export: '%s': not a valid identifier\n", cmd);
		*must_export = false ;
		return ;
	}
	while (cmd[++(*index_str)] != '=' && cmd[(*index_str)] != '\0')
	{
		if (!ft_isalpha(cmd[0]) || !isalnum(cmd[(*index_str)]))
		{
			if (cmd[0] != '+' && cmd[(*index_str)] == '+' \
			&& cmd[(*index_str) + 1] == '=')
			{
				*must_append = true;
				break ;
			}
			printf("minishell: export: '%s': not a valid identifier\n", cmd);
			*must_export = false ;
			break ;
		}
	}
}
//prob avec mode 2 et 5 et 7, quand teste dans l'ordre ca foire...
//mode 1 == existe, pas de =
//mode 2 == existe, avec = et = avant
//mode 3 == n'existe pas, = present
//mode 4 == n'existe pas, pas de =
//mode 5 == existe, avec = et pas = avant
//mode 6 == existe, avec = et = avant, mais en append 
//mode 7 == existe, avec = et pas = avant, mais en append 
//mode 8 == n'existe pas, = present mais en append
//(9 == n'existe pas, = present mais vide, en append)
//(10 == existe, avec = et pas egal avant, mais vide)
//(11 == existe, = present mais vide, en append)
int	ft_export(char **cmd, t_env_vars *vars)
{
	int		index;
	int		index_str;
	bool	must_export;
	bool	must_append;

	index = 0;
	if (!cmd[1])
		return (ft_env(cmd, vars, 1));
	while (cmd[++index])
	{
		index_str = -1;
		must_export = true;
		must_append = false;
		check_export_args(cmd[index], &must_export, &must_append, &index_str);
		if (must_export == true)
		{
			if (ft_must_export(must_append, cmd[index], index_str, vars))
				return (1);
		}
	}
	return (4);
}
