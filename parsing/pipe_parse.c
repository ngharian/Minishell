/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:53:07 by gdero             #+#    #+#             */
/*   Updated: 2024/12/13 15:11:45 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	error_pipe(char *str, int i)
{
	if (i == 0)
		return (1);
	--i;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		--i;
	if (i < 0 || str[i] == '<' || str[i] == '>' || str[i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token '|'\n", 50);
		return (1);
	}
	return (0);
}

static int	finish_line(char *line, int i)
{
	++i;
	while (line[i] == 32 || (line[i] > 8 && line[i] < 14))
		++i;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	pipe_case(char **line, int i, t_env_vars **env)
{
	if (ft_strlen(*line) == 1)
	{
		write(2, "minishell: syntax error near unexpected token '|'\n", 50);
		return (-3);
	}
	if (error_pipe(*line, i))
		return (-3);
	if (finish_line(*line, i))
		return (finish_pipe(line, i, env));
	return (i + 1);
}
