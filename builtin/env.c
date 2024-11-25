/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:11:33 by gdero             #+#    #+#             */
/*   Updated: 2024/11/13 17:54:46 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

//mode 0 == env ; mode 1 == export
int	ft_env(char **cmd, t_env_vars *vars, int mode)
{
	int		index;
	char	**temp;

	index = -1;
	if (mode == 0)
	{
		temp = vars->env;
		if (cmd[1])
		{
			printf("env: %s: No such file or directory\n", cmd[1]);
			return (6);
		}
	}
	else
		temp = vars->exp;
	while (temp[++index])
		printf("%s\n", temp[index]);
	if (mode == 0)
		return (6);
	else
		return (4);
}
