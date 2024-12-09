/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:25:38 by gdero             #+#    #+#             */
/*   Updated: 2024/12/09 12:53:27 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_the_pipes(t_commands **cmd)
{
	t_commands	*temp;
	int			texchange[2];

	temp = (*cmd);
	if (temp->next != NULL && temp->previous == NULL)
	{
		if (pipe(temp->exchange) < 0)
			print_exit_error("Error while using pipe()\n", NULL, 1);
		temp->outfile = temp->exchange[1];
		texchange[0] = temp->exchange[0];
	}
	while (temp->next != NULL)
	{
		if (temp->next != NULL && temp->previous != NULL)
		{
			temp->infile = texchange[0];
			if (pipe(temp->exchange) < 0)
				print_exit_error("Error while using pipe()\n", NULL, 1);
			temp->outfile = temp->exchange[1];
			texchange[0] = temp->exchange[0];
		}
		temp = temp->next;
	}
	if(temp->next == NULL && temp->previous != NULL)
		temp->infile = texchange[0];	
}

static void	infile_case(t_commands *cmd, t_file *file, t_here_doc **heredoc)
{
	t_here_doc	*temp;

	if (cmd->infile > 0)
		close(cmd->infile);
	if(access((*file).trimmed, R_OK) == -1 || access((*file).trimmed, F_OK) == -1)
	{
		cmd->error_file = ft_strdup((*file).trimmed);
		cmd->acces_file = 2;
		if(access((*file).trimmed, R_OK) == -1)
			cmd->acces_file = 1;
	}
	if ((*file).mode == 0 && (*file).type == '<')
		cmd->infile = open((*file).trimmed, O_RDONLY);
	else if ((*file).mode == 1 && (*file).type == '<')
	{
		cmd->infile = (*heredoc)->fd;
		temp = (*heredoc);
		(*heredoc) = (*heredoc)->next;
		free(temp);
	}
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
			close(cmd->outfile);
		if (access(trimmed, W_OK) == -1)
		{
			cmd->error_file = ft_strdup((*file).trimmed);
			cmd->acces_file = 1;
		}	
		if ((*file).mode == 0)
			cmd->outfile = open(trimmed, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if ((*file).mode == 1)
			cmd->outfile = open(trimmed, O_CREAT | O_WRONLY | O_APPEND, 0644);
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
