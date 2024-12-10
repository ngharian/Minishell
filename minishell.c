/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:28:50 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/10 16:39:55 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//volatile int g_signal;

/*
codes d'erreur que get_line peut recevoir d'une des fonctions qu'elle appele:
-1 = readline erreur (->quitter)
-2 = quottes unclosed (->continuer)
-3 = parsing erreur (->continue)
-4 = malloc error (->quitter)
-5 = empty_line -> (continue)
*/

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

static int	programme_loop(t_env_vars **env_vars, t_here_doc *here_doc, t_commands *cmd)
{
	char	*input;
	char	**splitted;

	while (1)
	{
		ft_set_sig(1);
		if (get_line(&input, &here_doc, env_vars))
			continue ;
		add_history(input);
		if (input == NULL)
			continue ;
		expander(&input, *env_vars); //checker que le strncmp soit TOUT ce qu'il y a avant le '=' && les MAJ importent !
		if (split_mini(input, &splitted, '|'))
			print_exit_error("Malloc error!\n", NULL, 1, NULL); //gerer l'erreur -> soit 1 soit 2 et tous les deux des malloc errors
		free(input);
		fill_cmd_struct(&cmd, splitted, &here_doc);
		ft_execution(&cmd, env_vars); //!! changer les printf par des sterror pour afficher derniere erreur systeme(no such file or directory, command not found, etc...)
		free_struct(&cmd, 0, env_vars);
	}
}
int main(int argc, char **argv, char **env)
{
	t_env_vars	*env_vars;

	(void)argc;
	(void)argv;
	update_shlvl(env);
	env_vars = (t_env_vars *)malloc(sizeof(t_env_vars));
	if (!env_vars)
		print_exit_error("Malloc error", NULL, 1, NULL);
	fill_env(env, env_vars);
	env_vars->exit_code = 0;
	g_signal = 0;
	programme_loop(&env_vars, NULL, NULL);
}
