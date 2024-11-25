/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:12:28 by gdero             #+#    #+#             */
/*   Updated: 2024/11/25 14:03:59 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	ft_exit(t_commands *cmd, char *lower_cmd, t_env_vars *vars) // exit 123 coucou n'exit pas --> PAS FINI
{
	int	index;
	if (cmd->previous != NULL || cmd->next != NULL) //rentre la dedans quand exit seul ???
			return (7);
	if (cmd->cmd[1])
	{
		index = -1;
		while (cmd->cmd[1][++index])
		{
			if (!ft_isdigit(cmd->cmd[1][index]))
			{
				printf("minishell: exit: numeric argument required\n");
				break ;
			}
		}
		if (cmd->cmd[2])
			printf("minishell: exit: too many arguments\n");
		return (7);
	}
	else
	{
		free_struct(&cmd, 0);
		free_env(vars, 0);
		free(lower_cmd);
		printf("exit\n");
		exit(0);
	}
}
