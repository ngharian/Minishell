/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:25:38 by gdero             #+#    #+#             */
/*   Updated: 2024/12/04 13:41:51 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	infile_case(t_commands *cmd, t_file *file, t_here_doc **heredoc)
{
	t_here_doc	*temp;

	if (cmd->infile > 0)
		close(cmd->infile);
	if ((*file).mode == 0 && (*file).type == '<')
		cmd->infile = open((*file).trimmed, O_RDONLY);
	else if ((*file).mode == 1 && (*file).type == '<')
	{
		cmd->infile = (*heredoc)->fd;
		temp = (*heredoc);
		(*heredoc) = (*heredoc)->next;
		free(temp);
	}
	if (cmd->infile == -1)
		cmd->errno_file = errno;
}

static void	open_files(t_commands *cmd, t_file *file, t_here_doc **hd)
{
	char	*trimmed;

	trimmed = (*file).trimmed;
	if (cmd->infile < 0 || cmd->outfile < 0)
		return (free((*file).trimmed));
	if ((*file).type == '>')
	{
		if (cmd->outfile > 0)
		{
			if (cmd->outfile == cmd->exchange[1])
				write(cmd->outfile, "\0", 1);
			close(cmd->outfile);
		}
		if ((*file).mode == 0)
			cmd->outfile = open(trimmed, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if ((*file).mode == 1)
			cmd->outfile = open(trimmed, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (cmd->outfile == -1)
			cmd->errno_file = errno;
	}
	infile_case(cmd, file, hd);
	free(trimmed);
}

void	checking_in_and_out(t_commands *cmd, char *splitted, t_here_doc **hd)
{
	int		str_index;
	t_file	file;

	str_index = -1;
	while (splitted[++str_index])
	{
		if (splitted[str_index] == 39 || splitted[str_index] == '"')
			str_index = skip_quotes(splitted, str_index);
		if (splitted[str_index] == '\0')
			return ;
		else if (splitted[str_index] == '>' || splitted[str_index] == '<')
		{
			/*file.type = splitted[str_index];
			file.mode = 0;
			if (splitted[str_index] == splitted[str_index + 1])
				file.mode = 1;
			file.trimmed = ft_strchr(splitted, file.type);
			if(file.type =='>')
				file.trimmed = ft_strtrim(file.trimmed, "> ");
			else
				file.trimmed = ft_strtrim(file.trimmed, "< ");
			if (!file.trimmed)
				return (1);
			update_trim_string(file.trimmed);
			update_string(&splitted, file.trimmed, file.mode, file.type);
			if (cmd_without_quotes(&file.trimmed))
				return (1);*/
			//trimmed = ft_strtrim(trimmed, "\"'");
			get_file_name_trimmed(&file, &str_index, &splitted);
			open_files(cmd, &file, hd);
			if (splitted[str_index] == '\0')
				break ;
		}
	}
}
