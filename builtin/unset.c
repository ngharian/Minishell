/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:13:48 by gdero             #+#    #+#             */
/*   Updated: 2024/12/13 15:07:23 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static void	delete_var(char **vars, char *str, int str_len, int iteration)
{
	int		index;
	char	*temp;

	index = -1;
	while (vars[++index])
	{
		if (iteration == 0)
			temp = vars[index] + 11;
		else
			temp = vars[index];
		if ((ft_strncmp(str, temp, str_len) == 0 \
		&& (temp[str_len] == '\0' || temp[str_len] == '=')))
		{
			free(vars[index]);
			index--;
			while (vars[++index])
				vars[index] = vars[index + 1];
			vars[index] = NULL;
			break ;
		}
	}
}

int	is_there_equal(char *str, int mode)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (str[index] == '=')
		{
			if (mode == 1)
				return (index);
			return (1);
		}
	}
	if (mode == 1)
		return (index);
	return (0);
}

static int	is_there_spe_char(char *cmd)
{
	int	index;

	index = -1;
	while (cmd[++index])
	{
		if (!isalnum(cmd[index]))
			return (1);
	}
	return (0);
}

int	ft_unset(char **cmd, t_env_vars *vars)
{
	int	index;
	int	exit_code;
	int	str_len;

	index = 0;
	exit_code = 0;
	while (cmd[++index])
	{
		str_len = ft_strlen(cmd[index]);
		if (!ft_isalpha(cmd[index][0]) || is_there_equal(cmd[index], 0) \
		|| is_there_spe_char(cmd[index]))
		{
			print_exit_error("not a valid identifier", \
			cmd[index], -1, "unset: ");
			exit_code = 1;
			continue ;
		}
		delete_var(vars->exp, cmd[index], str_len, 0);
		delete_var(vars->env, cmd[index], str_len, 1);
		continue ;
	}
	return (exit_code);
}
