/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:32:56 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/17 17:46:14 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signal;

bool	check_empty_line(char *buffer)
{
	while (*buffer)
	{
		if (*buffer != 32 || *buffer < 8 || *buffer > 14)
			return (false);
		buffer++;
	}
	return (true);
}

int	quote_case(char *str, int i)
{
	char	type_quote;

	type_quote = str[i++];
	while (str[i] != type_quote)
	{
		if (str[i] == '\0')
		{
			write(2, "minishell: Quotes unclosed! please retry\n", 41);
			return (-2);
		}
		++i;
	}
	return (i + 1);
}

void	ft_free_here_doc(t_here_doc **heredoc)
{
	t_here_doc	*temp;

	while ((*heredoc) != NULL)
	{
		close((*heredoc)->fd);
		temp = (*heredoc);
		*heredoc = (*heredoc)->next;
		free (temp);
	}
}

int	verif_line(char **readed_line, \
t_here_doc **hd, t_env_vars **env_vars, int i)
{
	while ((*readed_line)[i] != '\0')
	{
		if ((*readed_line)[i] == '"' || (*readed_line)[i] == 39)
			i = quote_case(*readed_line, i);
		else if ((*readed_line)[i] == '<' || (*readed_line)[i] == '>')
			i = arrow_case(*readed_line, i, hd, env_vars);
		else if ((*readed_line)[i] == '|')
			i = pipe_case(readed_line, i);
		else
			++i;
		if (i < 0)
		{
			add_history(*readed_line);
			ft_free_here_doc(hd);
			return (exit_parsing(i, env_vars));
		}
	}
	return (0);
}

int	get_line(char **readed_line, t_here_doc **heredoc, t_env_vars **env_vars)
{
	*readed_line = readline("minishell$ ");
	if (!(*readed_line))
		exit_parsing(-1, env_vars);
	if (check_empty_line(*readed_line))
		return (exit_parsing(0, env_vars));
	if (g_signal == SIGINT)
	{
		(*env_vars)->exit_code = 130;
		g_signal = 0;
	}
	return (verif_line(readed_line, heredoc, env_vars, 0));
}
