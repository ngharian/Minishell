/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngharian <ngharian@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:32:56 by ngharian          #+#    #+#             */
/*   Updated: 2024/11/22 14:40:22 by ngharian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_empty_line(char *buffer)
{
	while (*buffer)
	{
		if (*buffer != 32 || *buffer < 8 || *buffer > 14)
			return (false);
		buffer++;
	}
	return (true);
}

int	quote_case(char *str, int i)
{
	char	type_quote;

	type_quote = str[i++];
	while (str[i] != type_quote)
	{
		if (str[i] == '\0')
		{
			printf("end of line\n");
			return (-2);
		}
		++i;
	}
	return (i + 1); //ajoute + 1 ici, sinon reprend le 2e " et refait le traitenent -> ira always dans quote non fermee
}

/*
codes d'erreur que get_line peut recevoir d'une des fonctions qu'elle appele:
-1 = readline erreur (->quitter)
-2 = quottes unclosed (->continuer)
-3 = parsing erreur (->continue)
-4 = malloc error (->quitter)
-5 = empty_line -> (continue)
-6 = ctrl+c (-> continuer + exit code = 1)
*/
/*char 	*exit_parsing(int i) // testing purpose
{
	if (i == -2)
		write(1, "Non closed quotes->undefined behavior in bash\n", 46);
	if (i == -1 || i == -4)
		write(1, "Malloc error while parsing\n", 27);
	return (NULL); // !!! Probleme quand on veut aller plus haut dans l'historique apres etre passe par ici
}*/

int	get_line(char **readed_line, t_here_doc **heredoc, t_env_vars **env_vars)
{
	int		i;

	i = 0;
	//printf("%s ", get_path_line((*env_vars)->env, "PWD="));
	*readed_line = readline("minishell$ ");
    if (!(*readed_line))
		exit_parsing(-1);
	if (check_empty_line(*readed_line))
		return (exit_parsing(0));
	if (g_signal == SIGINT) // !!! valeur d'erreur processus bloquant? comment gerer?
	{
		(*env_vars)->exit_code = 1;
		g_signal = 0;
	}
	while ((*readed_line)[i] != '\0')
	{
		if ((*readed_line)[i] == '"' || (*readed_line)[i] == 39)
			i = quote_case(*readed_line, i); //si croise un guillemet, skip jusqu'à celui correspondant. si \0, erreur
		else if ((*readed_line)[i] == '<' || (*readed_line)[i] == '>')
			i = arrow_case(*readed_line, i, heredoc, *env_vars);
		else if ((*readed_line)[i] == '|')
			i = pipe_case(readed_line, i); //erreur si pipe au debut, join si pipe à la fin.
		else
			++i;
		if (i < 0)
		{
			add_history(*readed_line);
			return (exit_parsing(i/*, env_vars*/)); //se chargera d'afficher le message d'erreur correspondant
									 //à la valeur de i, donner le code d'erreur à $? puis
									 //exit si nécessaire, sinon reprendre à l'input (en retournant NULL). + free readad line
		}
	}
	return (0);
}
