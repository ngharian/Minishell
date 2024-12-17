/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:28:50 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/17 17:46:53 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal;

static void	update_shlvl(char **env)
{
	int			shellvl;
	char		*shlvl;
	char		*shlvlchar;
	int			index;

	index = -1;
	shellvl = ft_atoi(get_path_line(env, "SHLVL=", 1) + 1);
	shellvl++;
	shlvlchar = ft_itoa(shellvl);
	if (!shlvlchar)
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
	shlvl = ft_strjoin("SHLVL=", shlvlchar);
	free(shlvlchar);
	if (!shlvl)
		print_exit_error("Malloc error!\n", NULL, 1, NULL);
	while (env[++index])
	{
		if (ft_strncmp(env[index], "SHLVL=", 6) == 0)
			env[index] = shlvl;
	}
}

static void	programme_loop(t_env_vars **env_vars, \
							t_here_doc *here_doc, t_commands *cmd)
{
	char	*input;
	char	**splitted;

	while (1)
	{
		ft_set_sig(1);
		update_cwd(env_vars, 0);
		if (get_line(&input, &here_doc, env_vars))
			continue ;
		add_history(input);
		if (input == NULL)
			continue ;
		expander(&input, *env_vars);
		if (split_mini(input, &splitted, '|'))
			print_exit_error("Malloc error!\n", NULL, 1, NULL);
		free(input);
		fill_cmd_struct(&cmd, splitted, &here_doc);
		ft_execution(&cmd, env_vars);
		free_struct(&cmd, 0, env_vars);
	}
}

char	**construct_env(char **env)
{
	char	cwd[1024];

	env = malloc(sizeof(char *) * 4);
	if (!env)
		print_exit_error("Malloc error", NULL, 1, NULL);
	env[0] = malloc(sizeof(char) * 8);
	env[1] = malloc(sizeof(char) * 14);
	if (!env[0] || !env[1])
		print_exit_error("Malloc error", NULL, 1, NULL);
	env[0] = "SHLVL=0";
	env[1] = "_=./minishell";
	env[3] = NULL;
	env[2] = getcwd(cwd, sizeof(cwd));
	if (!env[2])
		print_exit_error("get_cwd() error", NULL, 1, NULL);
	env[2] = ft_strjoin("PWD=", env[2]);
	if (!env[2])
		print_exit_error("Malloc error", NULL, 1, NULL);
	return (env);
}

static void	handle_argv(char **argv)
{
	int		i;
	char	*join;

	i = 0;
	while (argv[++i])
	{
		join = ft_strjoin("/usr/local/bin/", argv[i]);
		if (access(join, X_OK) == 0)
			print_exit_error("cannot execute binary file", join, 126, NULL);
		else
			print_exit_error("No such file or directory", join, 127, NULL);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env_vars	*env_vars;
	char		buffer[1024];

	(void)argc;
	(void)argv;
	if (argc > 1)
		handle_argv(argv);
	if (!env[0])
		env = construct_env(NULL);
	update_shlvl(env);
	env_vars = (t_env_vars *)malloc(sizeof(t_env_vars));
	if (!env_vars)
		print_exit_error("Malloc error", NULL, 1, NULL);
	fill_env(env, env_vars);
	env_vars->mini_root = getcwd(buffer, sizeof(buffer));
	if (!env_vars->mini_root)
		print_exit_error("get_cwd() error", NULL, 1, NULL);
	env_vars->exit_code = 0;
	g_signal = 0;
	programme_loop(&env_vars, NULL, NULL);
}
