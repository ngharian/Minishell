/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:39:28 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/13 13:55:14 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	arrow_error(char *readed_line, int i)
{
	if ((readed_line[i - 1] == '<' && readed_line[i] == '<')
		|| (readed_line[i - 1] == '>' && readed_line[i] == '>'))
		++(i);
	while (readed_line[i] == 32
		|| (readed_line[i] > 8 && readed_line[i] < 14))
		++(i);
	if (readed_line[i] == '\0')
	{
		write(2, "minishell: ", 11);
		return (write(2, "Syntax error near unexpected token 'newline'\n", 45));
	}
	if (readed_line[i] == '<' || readed_line[i] == '>')
	{
		write(2, "minishell: Syntax error near unexpected token ", 46);
		if (readed_line[i] == '<' && readed_line[i + 1] == '<')
			write(2, "'<<'\n", 5);
		else if (readed_line[i] == '>' && readed_line[i + 1] == '>')
			write(2, "'>>'\n", 5);
		else if (readed_line[i] == '<')
			write(2, "'<'\n", 4);
		else
			write(2, "'>'\n", 4);
		return (1);
	}
	return (0);
}

int	arrow_case(char *readed_line, int i, \
t_here_doc **heredoc, t_env_vars **env_vars)
{
	++i;
	if (arrow_error(readed_line, i))
		return (-3);
	i = ft_here_doc(heredoc, readed_line, i, env_vars);
	if (i > 0)
	{
		if ((readed_line[i - 1] == '<' && readed_line[i] == '<')
			|| (readed_line[i - 1] == '>' && readed_line[i] == '>'))
			++i;
	}
	return (i);
}
