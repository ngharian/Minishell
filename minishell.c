/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:28:50 by ngharian          #+#    #+#             */
/*   Updated: 2024/12/06 12:33:37 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int g_signal;

/*
codes d'erreur que get_line peut recevoir d'une des fonctions qu'elle appele:
-1 = readline erreur (->quitter)
-2 = quottes unclosed (->continuer)
-3 = parsing erreur (->continue)
-4 = malloc error (->quitter)
-5 = empty_line -> (continue)
*/

void	print_cmd(t_commands *cmd)
{
	int	i = 0;
	int	j = 0;
	while(cmd != NULL)
	{
		printf("struct %d:\n", j);
		printf("infile: %d outfile : %d \n", cmd->infile, cmd->outfile);
		i = 0;
		printf("ligne: ");
		while(cmd->cmd[i])
		{
			printf("%s[]", cmd->cmd[i]);
			++i;
		}
		printf("\n");
		++j;
		cmd = cmd->next;
	}
}

static int	update_shlvl(char **env)
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
		return (1);
	shlvl = ft_strjoin("SHLVL=", shlvlchar);
	free(shlvlchar);
	if (!shlvl)
		return (1);
	while (env[++index])
	{
		if (ft_strncmp(env[index], "SHLVL=", 6) == 0)
			env[index] = shlvl;
	}
	return (0);
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
		if (expander(&input, *env_vars)) //checker que le strncmp soit TOUT ce qu'il y a avant le '=' && les MAJ importent !
			exit(1);
		if (split_mini(input, &splitted, '|'))
			print_exit_error("Malloc error!\n", 1); //gerer l'erreur -> soit 1 soit 2 et tous les deux des malloc errors
		if (fill_cmd_struct(&cmd, splitted, &here_doc))
			print_exit_error("fill_struct_err\n", 1); //erreur -> 1 = malloc error pour les structs ; 2 = malloc error pour les strings sans quotes
		if (execution(&cmd, env_vars))
			print_exit_error("Exec error\n", 1); //!! changer les printf par des sterror pour afficher derniere erreur systeme(no such file or directory, command not found, etc...)
		/*if (ft_builtins(cmd, env_vars))
			exit (1);*/
		free_struct(&cmd, 0);
	}
}
int main(int argc, char **argv, char **env)
{
	t_env_vars	*env_vars;

	(void)argc;
	(void)argv;
	if (update_shlvl(env))
		exit(0);
	env_vars = (t_env_vars *)malloc(sizeof(t_env_vars));
	if (fill_env(env, env_vars))
		return (1);
	env_vars->exit_code = 0;
	if (!env_vars)
		return (1);
	g_signal = 0;
	programme_loop(&env_vars, NULL, NULL);
}

