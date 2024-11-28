#include "../minishell.h"

static int	get_len_heredoc(char *line, int *i, int len, int j)
{
	while (line[*i] != 32 && (line[*i] < 8 || line[*i] > 14) && line[*i])
	{
		if (line[*i] == '"' || line[*i] == 39)
		{
			*i = skip_quotes(line, *i);
			len = *i - j;
		}
		else
		{
			++len;
			++(*i);
		}
	}
	return(len);
}

char	*find_eof(char *line, int i)
{
	char	*eof;
	int		len;
	int		j;

	while (line[i] == 32 || (line[i] > 8 && line[i] < 14))
		++i;
	j = i;
	len = 0;
	len = get_len_heredoc(line, &i, len, j);
	eof = malloc(sizeof(char) * (len + 1));
	if (!eof)
		return (NULL);
	i = j;
	j = 0;
	while (j < len)
	{
		eof[j] = line[i++];
		++j;
	}
	eof[j] ='\0';
	cmd_without_quotes(&eof);
	return (eof);
}
