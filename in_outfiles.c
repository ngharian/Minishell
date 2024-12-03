/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_outfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:25:38 by gdero             #+#    #+#             */
/*   Updated: 2024/12/03 13:16:35 by ngharian         ###   ########.fr       */
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

static void infile_case(t_commands *cmd, t_file *file, t_here_doc **heredoc)
{
	t_here_doc	*temp;
	
	if (cmd->infile > 0)
		close(cmd->infile);
    if ((*file).mode == 0 && (*file).type == '<')
		cmd->infile = open((*file).trimmed, O_RDONLY);
	else if((*file).mode == 1 && (*file).type == '<')
	{
		cmd->infile = (*heredoc)->fd;
		temp = (*heredoc);
		(*heredoc) = (*heredoc)->next;
		free(temp);
	}
	if (cmd->infile == -1)
			cmd->errno_file = errno;
}

static void	open_files(t_commands *cmd, t_file *file, t_here_doc **heredoc)
{
	char	*trimmed;
	
	trimmed = (*file).trimmed;
	if (cmd->infile < 0 || cmd->outfile < 0)
		return (free((*file).trimmed));
	if ((*file).type == '>')
	{
		if (cmd->outfile > 0)
			close(cmd->outfile);
		if ((*file).mode == 0)
			cmd->outfile = open(trimmed, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if ((*file).mode == 1)
			cmd->outfile = open(trimmed, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (cmd->outfile == -1)
			cmd->errno_file = errno;
	}
	infile_case(cmd, file, heredoc);
	free(trimmed);
}

static void	update_trim_string(char *trimmed)
{
	int	str_index;

	str_index = 0;
	while (trimmed[str_index])
	{
		if (trimmed[str_index] == 39 || trimmed[str_index] == '"')
		{
			str_index = skip_quotes(trimmed, str_index);
			continue ;
		}
		if (trimmed[str_index] == ' ' || trimmed[str_index] == '\0')
			break ;
		str_index++;
	}
	ft_strlcpy(trimmed, trimmed, str_index + 1);
}

int	checking_in_and_out(t_commands *cmd, char *splitted, t_here_doc **heredoc)
{
	int		str_index;
	t_file	file;

	str_index = -1;
	while (splitted[++str_index])
	{
		if (splitted[str_index] == 39 || splitted[str_index] == '"')
			str_index = skip_quotes(splitted, str_index);
		if (splitted[str_index] == '\0')
			return (0);
		if (splitted[str_index] == '>' || splitted[str_index] == '<')
		{
			file.type = splitted[str_index];
			//mode = is_double(splitted, type);
			file.mode = 0;
			if (splitted[str_index] == splitted[str_index + 1])
				file.mode = 1;
			file.trimmed = ft_strchr(splitted, file.type);
			printf("trimmed: %s\n", file.trimmed);
			file.trimmed = ft_strtrim(file.trimmed, "> <");
			if (!file.trimmed)
			{
				printf("ici");
				return (1);
			}
			update_trim_string(file.trimmed);
			update_string(&splitted, file.trimmed, file.mode, file.type);
			if (cmd_without_quotes(&file.trimmed))
				return (1);
			//trimmed = ft_strtrim(trimmed, "\"'");
			open_files(cmd, &file, heredoc);
			if (file.mode == 1)
				++str_index;
		}
	}
	return (0);
}
