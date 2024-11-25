/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:10:16 by gdero             #+#    #+#             */
/*   Updated: 2024/11/06 17:31:37 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static void	check_for_n(char **cmd, int *index, bool *must_new_line)
{
	int	nb_char;

	while (cmd[*index] && strncmp(cmd[*index], "-", 1) == 0)
	{
		nb_char = 1;
		while (cmd[*index][nb_char])
		{
			if (cmd[*index][nb_char] != 'n')
				return ;
			nb_char++;
		}
		*must_new_line = false;
		*index = *index + 1;
	}
	return ;
}

int	ft_echo(char **cmd)
{
	int		index;
	bool	must_new_line;

	index = 1;
	must_new_line = true;
	if (cmd[index])
		check_for_n(cmd, &index, &must_new_line);
	while (cmd[index])
	{
		if (!cmd[index + 1])
		{
			printf("%s", cmd[index]);
			break ;
		}
		printf("%s ", cmd[index]);
		index++;
	}
	if (must_new_line)
		printf("\n");
	return (1);
}
