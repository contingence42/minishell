/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:20:21 by kdaumont          #+#    #+#             */
/*   Updated: 2024/02/15 09:31:31 by aattali          ###   ########.fr       */
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
	minishell->env = ft_stradup(envp);
	show_prompt();
	(void)argc;
	(void)argv;
	ft_free_astr(minishell->env);
	free(minishell);
	return (EXIT_SUCCESS);
}
