/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:39:11 by ngharian          #+#    #+#             */
/*   Updated: 2024/11/28 17:05:36 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fill_heredoc(int fd, char *line, int i, t_env_vars *env_vars)
{
	char	*readed;
	char	*eof_string;

	eof_string = find_eof(line, i + 1);
	signal(SIGINT, exit);
	while (1)
	{
		readed = readline("here_doc >");
		if (!readed || !eof_string)
			print_exit_error("Exit...\n", 4);
		if (ft_strncmp(readed, eof_string, ft_strlen(eof_string)) == 0)
		{
			write(fd, "\0", 1);
			exit(3);
		}
		if (expander(&readed, env_vars))
			exit(EXIT_FAILURE);
		write(fd, readed, ft_strlen(readed));
		write(fd, "\n", 1);
		free(readed);
	}
}

int ft_wait_single_process(int status, pid_t pid, int fd, int i)
{
	ft_set_sig(2);
    while (1 && pid)
	{
		if (waitpid(pid, &status, WNOHANG) < 0)
            print_exit_error("Error while using 'waitpid()'\n", 1);
		if (status >> 8 != 0)
		{
			if ((status >> 8) == EXIT_FAILURE)
				exit(EXIT_FAILURE);
			if ((status >> 8) == 4)
				exit(0);
			if((status >> 8) == SIGINT)
			{
				close(fd);
				return (-6);
			}
			return (i);
		}
	}
	return (i);
}
t_here_doc *find_last_heredoc(t_here_doc *here_doc)
{
	if(!here_doc)
		return (NULL);
	while(here_doc->next)
		here_doc = here_doc->next;
	return (here_doc);
}

static void	alloc_heredoc(t_here_doc **here_doc, int fd)
{
	t_here_doc	*new_element;
	t_here_doc	*last;
	t_here_doc	*first;

	first = *here_doc;
	new_element = malloc(sizeof(t_here_doc));
	if (!new_element)
		print_exit_error("Malloc Error!\n", 1);
	new_element->previous = NULL;
	new_element->fd = fd;
	new_element->next = NULL;
	if(*here_doc == NULL)
		*here_doc = new_element;
	else
	{
		last = find_last_heredoc(*here_doc);
		last->next = new_element;
		new_element->previous = last;
	}
}

int	ft_here_doc(t_here_doc **heredoc, char *readed_line, int i, t_env_vars *env_vars)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	int		ret;

	status = 0;
    pid = 0;
	if (!(readed_line[i] == '<' && readed_line[i - 1] == '<'))
		return (i);
	if (pipe(pipefd) == -1)
		print_exit_error("Error while using 'pipe()'\n", 1);
	alloc_heredoc(heredoc, pipefd[0]);
	pid = fork();
	if (pid < 0)
		print_exit_error("Error while using 'fork()'\n", 1);
	if (pid == 0)
		fill_heredoc(pipefd[1], readed_line, i, env_vars);
	close(pipefd[1]);
    ret = ft_wait_single_process(status, pid, pipefd[0], i);
	ft_set_sig(1);
	return(ret);
}
