/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:23:38 by aattali           #+#    #+#             */
/*   Updated: 2024/02/14 10:18:00 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check if piping will be needed, and toggle the flag
 *
 * @param minishell the struct of the program
 * @param command the linked-list of commands
 */
void	pipe_needed(t_minishell *minishell, t_commands *command)
{
	size_t	i;

	i = 0;
	while (command)
	{
		if (!command->builtin)
			i++;
		command = command->next;
	}
	if (i > 1)
		minishell->ispipe = true;
}

/**
 * @brief close the pipe
 *
 * @param pipe the pipe given
 */
void	close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

/**
 * @brief check if the pipe will be broken by a builtin
 *
 * a builtin is never forked, so the piping doesn't work,
 * the input will be discarded and no output will be given to subsequent pipes
 * thus we need to check if this is the case to "clean" the pipe
 *
 * @param command the linked-list of commands
 * @return the boolean of the cond
 */
bool	isbroken_pipe(t_commands *command)
{
	return (!command->next || command->next->builtin);
}
