/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_outfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:25:38 by gdero             #+#    #+#             */
/*   Updated: 2024/11/11 15:41:44 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_string(char **splitted, char *trimmed, int mode, char c)
{
	int	index;
	int	trim_index;

	index = 0;
	trim_index = 1;
	while ((*splitted)[index] != c)
		index++;
	if (mode == 1)
		trim_index++;
	while ((*splitted)[index + trim_index] == ' ')
		trim_index++;
	trim_index += ft_strlen(trimmed);
	while ((*splitted)[index + trim_index])
	{
		(*splitted)[index] = (*splitted)[index + trim_index];
		index++;
	}
	(*splitted)[index] = '\0';
}

static void infile_case(t_commands *cmd, char *trimmed, int mode, char c)
{
    if (mode == 0 && c == '<')
	{
		if (cmd->infile > 0)
			close(cmd->infile);
		cmd->infile = open(trimmed, O_RDONLY);
		if (access(trimmed, F_OK) == -1)
		{
			cmd->infile = -1;
			printf("minishell: %s: No such file or directory\n", trimmed);
		}
		else if (access(trimmed, R_OK) == -1)
		{
			cmd->infile = -1;
			printf("minishell: %s: Permission denied\n", trimmed);
		}
	}
}

static void	open_files(t_commands *cmd, char *trimmed, int mode, char c)
{
	if (cmd->infile < 0)
		return (free(trimmed));
	if (c == '>')
	{
		if (cmd->outfile > 0)
			close(cmd->outfile);
		if (mode == 0)
			cmd->outfile = open(trimmed, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (mode == 1)
			cmd->outfile = open(trimmed, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (access(trimmed, W_OK) == -1)
			printf("minishell: %s: Permission denied\n", trimmed);
	}
	infile_case(cmd, trimmed, mode, c);
	free(trimmed);
}

static void	update_trim_string(char *trimmed)
{
	int	str_index;

	str_index = 0;
	while (trimmed[str_index])
	{
		if (trimmed[str_index] == 39 || trimmed[str_index] == '"')
			str_index = skip_quotes(trimmed, str_index);
		if (trimmed[str_index] == ' ' || trimmed[str_index] == '\0')
			break ;
		str_index++;
	}
	ft_strlcpy(trimmed, trimmed, str_index + 1);
}

int	checking_in_and_out(t_commands *cmd, char *splitted, char type)
{
	int		str_index;
	int		mode;
	char	*trimmed;

	str_index = -1;
	while (splitted[++str_index])
	{
		if (splitted[str_index] == '>' || splitted[str_index] == '<')
		{
			type = splitted[str_index];
			mode = is_double(splitted, type);
			trimmed = ft_strchr(splitted, type);
			if (trimmed == NULL)
				break ;
			trimmed = ft_strtrim(trimmed, "> <");
			if (!trimmed)
				return (1);
			update_trim_string(trimmed);
			update_string(&splitted, trimmed, mode, type);
			if (cmd_without_quotes(&trimmed))
				return (1);
			open_files(cmd, trimmed, mode, type);
		}
	}
	return (0);
}
