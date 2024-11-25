#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include "Libft/libft.h"
#include <stdbool.h>
#include <signal.h>
#include <termios.h>

volatile int g_signal;

typedef struct s_commands
{
	int					infile;
	int					outfile;
	bool				builtin;
	int					exchange[2];
	char				**cmd;
	int					right_command;
	pid_t				process;
	int					last_cmd;
	struct s_commands	*previous;
	struct s_commands	*next;
}	t_commands;

typedef struct	s_here_doc
{
	struct s_here_doc	*previous;
	int	fd;
	struct s_here_doc	*next;
}	t_here_doc ;

typedef struct	s_env_vars
{
	char	**env;
	char	**exp;
	int		nb_string;
	unsigned char	exit_code;
	pid_t	pid;
	char	*paths;
	char	**split_path;
	char	**true_paths;
}	t_env_vars;

void	rl_replace_line(const char *text, int clear_undo);
int		split_mini(char *s, char ***array, char to_split);

int		fill_cmd_struct(t_commands **cmd, char **splitted);

//signaux
void	ft_set_sig(int mode);
void	ft_init_signal(void);
void	sigint_process(int signal);
void	default_sigint(int sig);
void	sigint_block(int sig);

//parsing
int		fill_env(char **env, t_env_vars *vars);
int		get_line(char **readed_line, t_here_doc **heredoc, t_env_vars **env_vars);
int		quote_case(char *str, int i);
bool	check_empty_line(char *buffer);
int		pipe_case(char **line, int i);
int		arrow_case(char *readed_line, int i, t_here_doc **pipe_hd, t_env_vars *env_vars);
int		ft_here_doc(t_here_doc **heredoc, char *readed_line, int i, t_env_vars *env_vars);
int		ft_wait_single_process(int status, pid_t pid, int fd, int i);
int		expander(char **input, t_env_vars *vars);
int		finish_pipe(char **line, int i);
int		checking_in_and_out(t_commands *cmd, char *splitted, char type);
int		is_double(char *splitted, char c);

//del_quotes
int		delete_quotes(t_commands *cmd);
int		cmd_without_quotes(char **string);

//frees & exit
void	free_split(char **split);
int		free_struct(t_commands **cmd, int error);
int		exit_parsing(int mode);
void	print_exit_error(char *message, int exit_code);

//execution
int		execution(t_commands **cmd, t_env_vars **vars);
int		skip_quotes(char *str, int str_j);

//builtin
int		ft_builtins(t_commands *cmd, t_env_vars *vars);
char	*add_char(char *env, int mode);
void	make_order(t_env_vars *vars, int index);
int		ft_cd(t_commands *cmd, t_env_vars *vars);
int		ft_echo(char **cmd);
int		ft_env(char **cmd, t_env_vars *vars, int mode);
int		ft_exit(t_commands *cmd);
int		ft_export(char **cmd, t_env_vars *vars);
int		ft_pwd(char **cmd, t_env_vars *vars);
int		ft_unset(char **cmd, t_env_vars *vars);
int		is_there_equal(char *str, int mode);
int		already_exists(char *str, t_env_vars **vars, \
		int *index_mode, int index_str);
char	*get_path_line(char **env, char *line, int mode);


int	execute_cmd(t_env_vars *vars, t_commands *temp);