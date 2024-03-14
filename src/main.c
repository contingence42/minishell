/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:20:21 by aattali           #+#    #+#             */
/*   Updated: 2024/03/14 17:29:07 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief the global variable to store the signal code
 */
int	g_signal_code = 0;

/**
 * TODO: the function will take the minishell struct, will handle
 * the return values and call the general handler when the inpt is valid
 */
void	show_prompt(t_minishell *minishell)
{
	char	*inpt;
	int		i;

	i = 0;
	while (true)
	{
		signal_initializer();
		inpt = readline("minishell$ ");
		if (ft_strcmp(inpt, "exit") == 0)
			break ;
		if (ft_strcmp(inpt, "history -c") == 0)
			rl_clear_history();
		if (inpt && inpt[0])
		{
			add_history(inpt);
			handler(inpt, minishell);
		}
		printf("\n");
		++i;
	}
	(void)i;
}

/**
 * @brief initialise the env linked-list with the default environment
 *
 * @param env the linked-list to be created
 * @param envp the default environment
 */
int	init_env(t_env **env, char *envp[])
{
	size_t	i;

	i = -1;
	while (envp[++i])
		if (env_add_back(env, env_new(envp[i])) == EXIT_FAILURE)
			return (env_clear(env), malloc_error());
	return (EXIT_SUCCESS);
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
	int			code;

	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		return (malloc_error());
	minishell->env = NULL;
	minishell->code = EXIT_SUCCESS;
	if (init_env(&(minishell->env), envp) == EXIT_FAILURE)
		return (free(minishell), EXIT_FAILURE);
	show_prompt(minishell);
	(void)argc;
	(void)argv;
	env_clear(&(minishell->env));
	code = minishell->code;
	free(minishell);
	return (code);
}
