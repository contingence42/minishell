/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:20:21 by kdaumont          #+#    #+#             */
/*   Updated: 2024/02/15 13:54:57 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * TODO: the function will take the minishell struct, will handle
 * the return values and call the general handler when the inpt is valid
 */
void	show_prompt(void)
{
	char	*inpt;
	int		i;

	i = 0;
	while (true)
	{
		inpt = readline("minishell$ ");
		if (ft_strcmp(inpt, "exit") == 0)
			break ;
		if (ft_strcmp(inpt, "history -c") == 0)
			rl_clear_history();
		if (inpt && inpt[0])
			add_history(inpt);
		printf("\n");
		++i;
	}
}

/**
 * @brief initialise the env linked-list with the default environment
 *
 * @param env the linked-list to be created
 * @param envp the default environment
 */
void	init_env(t_env **env, char *envp[])
{
	size_t	i;

	i = -1;
	while (envp[++i])
		env_add_back(env, env_new(envp[i]));
}

/**
 * @brief starting point of minishell
 *
 * TODO:initialisation of default variables, then call to readline
 *
 * @param argc unused
 * @param argv unused
 * @param envp the environment
 * @return code
 */
int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	*minishell;

	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->env = NULL;
	init_env(&(minishell->env), envp);
	show_prompt();
	(void)argc;
	(void)argv;
	env_clear(&(minishell->env));
	free(minishell);
	return (EXIT_SUCCESS);
}
