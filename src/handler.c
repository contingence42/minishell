/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:32:25 by aattali           #+#    #+#             */
/*   Updated: 2024/02/20 14:33:34 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief print the required error message and return exit_failure
 *
 * @return exit_failure
 */
int	malloc_error(void)
{
	return (ft_dprintf(STDERR_FILENO, MALLOC_ERROR), EXIT_FAILURE);
}

/**
 * @brief handle the lexing, parsing and execution process
 *
 * TODO:error handling
 *
 * @param line the line given by readline
 * @param minishell the general struct of the program
 */
void	handler(char *line, t_minishell *minishell)
{
	t_lexer		*lex;
	t_executor	*executor;
	t_commands	*command;

	lex = lexer(line, minishell);
	if (!lex)
		return ;
	executor = NULL;
	command = NULL;
	if (parser(lex, &executor, &command) == EXIT_FAILURE)
	{
		lex_clear(&lex);
		free(executor);
		cmd_clear(&command);
		return ;
	}
	executor->env = &(minishell->env);
	minishell->code = the_executor(executor, command);
}
