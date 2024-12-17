/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:32:29 by gdero             #+#    #+#             */
/*   Updated: 2024/12/17 17:46:17 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*pipe_join(char *line, char *to_add)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc(sizeof(char) * (ft_strlen(to_add) + ft_strlen(line) + 1));
	if (!joined)
	{
		free(line);
		free(to_add);
		print_exit_error("Malloc Error", NULL, 1, NULL);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (line[++i])
		joined[i] = line[i];
	j = -1;
	i -= 1;
	while (to_add[++j])
		joined[++i] = to_add[j];
	free(line);
	free(to_add);
	joined[++i] = '\0';
	return (joined);
}

static void	complete_pipe(int outfile, char *line)
{
	char	*to_add;

	signal(SIGINT, exit);
	while (1)
	{
		to_add = readline("pipe>");
		if (!to_add)
			print_exit_error("unexpected end of file\nexit", \
			"syntax error", 258, NULL);
		if (check_empty_line(line))
			continue ;
		break ;
	}
	line = pipe_join(line, to_add);
	write(outfile, line, ft_strlen(line));
	write(outfile, "\0", 1);
	exit(3);
}

int	finish_pipe(char **line, int i)
{
	int		pipefd[2];
	pid_t	pid;
	int		ret;

	pid = 0;
	if (pipe(pipefd) == -1)
		print_exit_error("Error while using 'pipe()'", NULL, 1, NULL);
	pid = fork();
	if (pid < 0)
		print_exit_error("Error while using 'fork()'", NULL, 1, NULL);
	if (pid == 0)
		complete_pipe(pipefd[1], *line);
	ret = ft_wait_single_process(pid, pipefd[0], i);
	ft_set_sig(1);
	close(pipefd[1]);
	if (ret == -6)
		return (-6);
	free(*line);
	*line = get_next_line(pipefd[0]);
	close(pipefd[0]);
	if (line == NULL)
		print_exit_error("Error while using 'get_next_line()'", \
		NULL, 1, NULL);
	return (i + 1);
}
