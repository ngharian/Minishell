/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:13:12 by gdero             #+#    #+#             */
/*   Updated: 2024/12/09 18:04:44 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static int	does_exist(char *temp, int index_str, char *str)
{
	if (str[index_str] == '\0' && \
	(temp[index_str] == '\0' || temp[index_str] == '='))
		return (1);
	if (str[index_str] == '+' && temp[index_str] == '=')
		return (6);
	if (str[index_str] == '=' && temp[index_str] == '=')
		return (2);
	if (str[index_str] == '+' && temp[index_str] == '\0')
		return (7);
	if (str[index_str] == '=' && temp[index_str] == '\0')
		return (5);
	return (0);
}

static int	already_exists(char *str, t_env_vars **vars, \
int *index_mode, int index_str)
{
	int		index;
	char	*temp;

	index = -1;
	while ((*vars)->exp[++index])
	{
		temp = (*vars)->exp[index] + 11;
		if (ft_strncmp(str, temp, index_str) == 0)
		{
			*index_mode = index;
			return (does_exist(temp, index_str, str));
		}
	}
	*index_mode = -1;
	if (is_there_equal(str, 0))
	{
		if (str[index_str] == '+' && str[index_str - 1] != '=')
			return (8);
		return (3);
	}
	return (4);
}

static void	check_export_args(char *cmd, bool *must_export, int *index_str)
{
	if (cmd[0] == '=')
	{
		print_exit_error("not a valid identifier", cmd, -1, "export: ");
		*must_export = false ;
		return ;
	}
	while (cmd[++(*index_str)] != '=' && cmd[(*index_str)] != '\0')
	{
		if (!ft_isalpha(cmd[0]) || !isalnum(cmd[(*index_str)]))
		{
			if (cmd[0] != '+' && cmd[(*index_str)] == '+' \
			&& cmd[(*index_str) + 1] == '=')
				break ;
			print_exit_error("not a valid identifier", cmd, -1, "export: ");
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
	int		mode;
	int		index_mode;
	bool	must_export;

	index = 0;
	if (!cmd[1])
		return (ft_env(cmd, vars, 1));
	while (cmd[++index])
	{
		index_str = -1;
		must_export = true;
		check_export_args(cmd[index], &must_export, &index_str);
		if (must_export == true)
		{
			mode = already_exists(cmd[index], &vars, &index_mode, index_str);
			add_to_var(cmd[index], mode, &vars, &index_mode);
		}
	}
	return (4);
}
