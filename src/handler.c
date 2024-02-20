/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:32:25 by aattali           #+#    #+#             */
/*   Updated: 2024/02/20 09:36:11 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	parser(lex, &executor, &command);
	executor->env = &(minishell->env);
	the_executor(executor, command);
}
