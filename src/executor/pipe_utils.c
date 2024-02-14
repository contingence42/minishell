/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:23:38 by aattali           #+#    #+#             */
/*   Updated: 2024/02/14 10:04:39 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

bool	isbroken_pipe(t_commands *command)
{
	return (!command->next || command->next->builtin);
}
