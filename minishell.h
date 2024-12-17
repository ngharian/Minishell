/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:42:08 by gdero             #+#    #+#             */
/*   Updated: 2024/12/17 17:41:47 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*====================INCLUDES====================*/

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdarg.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "Libft/include/libft.h"
# include <stdbool.h>
# include <signal.h>
# include <termios.h>

/*====================COMMAND_STRUCT====================*/

typedef struct s_commands
{
	int					infile;
	int					outfile;
	int					exchange[2];
	char				**cmd;
	int					right_command;
	pid_t				process;
	int					last_cmd;
	bool				absolute_path;
	int					acces_file;
	char				*error_file;
	struct s_commands	*previous;
	struct s_commands	*next;
}	t_commands;

/*====================HD_STRUCT====================*/

typedef struct s_here_doc
{
	struct s_here_doc	*previous;
	int					fd;
	struct s_here_doc	*next;
}	t_here_doc;

/*====================ENV_STRUCT====================*/

typedef struct s_env_vars
{
	char				**env;
	char				**exp;
	int					nb_string;
	char				*paths;
	char				*mini_root;
	char				**split_path;
	char				**true_paths;
	unsigned long long	exit_code;
}	t_env_vars;

/*====================REDIRECTION_STRUCT====================*/

typedef struct s_file
{
	int		mode;
	char	type;
	char	*trimmed;
}	t_file;

/*====================SIGNAUX====================*/

void	ft_set_sig(int mode);
void	ft_set_sig_bis(int mode);
void	ft_init_signal(void);
void	sigint_process(int signal);
void	default_sigint(int sig);
void	sigint_block(int sig);
void	set_ctrl(int mode);

/*====================PARSING====================*/

void	fill_env(char **env, t_env_vars *vars);
int		get_line(char **readed_line, t_here_doc **heredoc, \
		t_env_vars **env_vars);
int		quote_case(char *str, int i);
bool	check_empty_line(char *buffer);
int		pipe_case(char **line, int i);
int		arrow_case(char *readed_line, int i, \
		t_here_doc **pipe_hd, t_env_vars **env_vars);
int		ft_here_doc(t_here_doc **heredoc, \
		char *readed_line, int i, t_env_vars **env_vars);
char	*find_eof(char *line, int i);
int		ft_wait_single_process(pid_t pid, int fd, int i);
void	expander(char **input, t_env_vars *vars);
void	exchange_vars(char **input, char *var, char *to_find, int *index);
int		finish_pipe(char **line, int i);
int		is_double(char *splitted, char c);

/*====================REDIRECTION====================*/

void	checking_in_and_out(t_commands *cmd, \
		char *splitted, t_here_doc **heredoc, int str_index);
void	get_file_name_trimmed(t_file *file, int *str_index, char **splitted);
void	in_the_pipes(t_commands **cmd);

/*====================DEL_QUOTES====================*/

void	delete_quotes(t_commands *cmd);
void	cmd_without_quotes(char **string);
char	**clean_args(char **split, int i, int index, int j);

/*====================FREES & EXIT====================*/
void	free_split(char **split);
int		free_struct(t_commands **cmd, int error, t_env_vars **env);
int		exit_parsing(int mode, t_env_vars **env);
void	print_exit_error(char *message, \
		char *name, int exit_code, char *builtin);
int		free_env(t_env_vars *vars, int error);

/*====================EXECUTION====================*/

void	ft_execution(t_commands **cmd, t_env_vars **vars);
int		skip_quotes(char *str, int str_j);
void	get_path(t_env_vars **p_vars, t_env_vars *vars, int index);
void	wait_process(t_commands **cmd, t_env_vars **vars);
int		ft_redirect(t_commands *cmd, int mode);
void	check_access(t_env_vars *vars, t_commands *temp);
int		ft_strrncmp(char *verif, char *base, int len);

/*====================BUILTINS====================*/

int		ft_builtins(t_commands *cmd, t_env_vars *vars);
void	add_char(char **env, int mode);
void	make_order(t_env_vars *vars, int index);
int		ft_cd(t_commands *cmd, t_env_vars *vars);
int		ft_echo(char **cmd, t_env_vars *vars, int index);
int		ft_env(char **cmd, t_env_vars *vars, int mode);
int		ft_exit(t_commands *cmd, t_env_vars *vars);
int		ft_export(char **cmd, t_env_vars *vars);
int		ft_pwd(t_env_vars *vars);
int		ft_unset(char **cmd, t_env_vars *vars);
int		is_there_equal(char *str, int mode);
void	add_to_var(char *str, int mode, t_env_vars **vars, int *index_mode);
void	add_to_exp(char *str, int mode, t_env_vars **vars, int *index_mode);
void	append_var(char **oldstring, char *to_append, int mode);
void	add_line_to_env(char ***env, char ***new_env, char *str, int mode);
char	*get_path_line(char **env, char *line, int mode);
void	update_oldpwd(char ***var, char *oldpwd, int mode);
void	update_cwd(t_env_vars **env, int mode);
void	change_pwd(char ***var, char *line, char *to_find);
void	compare_string_and_join(char **string, char *to_find, \
		char **oldpwd, char *line);

/*====================AUTRES====================*/

void	rl_replace_line(const char *text, int clear_undo);
int		split_mini(char *s, char ***array, char to_split);
void	fill_cmd_struct(t_commands **cmd, \
		char **splitted, t_here_doc **heredoc);

#endif
