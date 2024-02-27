/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:32:25 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:49:26 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"

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
 * @brief free the two linked-lists and the exec struct
 *
 * @param lex the linked list of lexed elements
 * @param exec the struct of the exec process
 * @param cmd the linked list of commands
 */
static void	clean_posthandle(t_lexer **lex, t_executor *exec, t_commands **cmd)
{
	lex_clear(lex);
	free(exec->outfn);
	free(exec->infn);
	free(exec->limiter);
	ft_free_astr(exec->path);
	free(exec);
	cmd_clear(cmd);
}

/**
 * @brief handle the lexing, parsing and execution process
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
	clean_posthandle(&lex, executor, &command);
	lex_clear(&lex);
}
