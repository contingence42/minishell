/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:32:25 by aattali           #+#    #+#             */
/*   Updated: 2024/02/20 10:37:31 by aattali          ###   ########.fr       */
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

void	clean_exit_hdl(t_lexer **lex, t_executor *executor, t_commands **command)
{
	lex_clear(lex);
	free(executor);
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
	executor = NULL;
	command = NULL;
	if (parser(lex, &executor, &command) == EXIT_FAILURE)
		return (clean_exit_hdl(&lex, executor, &command));
	executor->env = &(minishell->env);
	minishell->code = the_executor(executor, command);
}
