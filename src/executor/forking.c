/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:57:20 by aattali           #+#    #+#             */
/*   Updated: 2024/02/14 10:04:59 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief open, close and dup the necessary fds, for pipe, stdin and stdout
 *
 * @param command the linked list of command
 * @param minishell the struct of the program
 */
void	setup_fd(t_commands *command, t_minishell *minishell)
{
	bool	dup_failed;

	dup_failed = false;
	if (command->first && minishell->infile != EMPTY)
	{
		if (minishell->infile == DOUBLE)
			minishell->infile_fd = minishell->heredoc[0];
		else
			minishell->infile_fd = safe_open(minishell, 0);
		dup_failed |= dup2(minishell->infile_fd, STDIN_FILENO) < 0;
		close(minishell->infile_fd);
	}
	if (!command->last && minishell->ispipe)
		dup_failed |= dup2(minishell->pipe[1], STDOUT_FILENO) < 0;
	else if (minishell->outfile != EMPTY)
	{
		minishell->outfile_fd = safe_open(minishell, 1);
		dup_failed |= dup2(minishell->outfile_fd, STDOUT_FILENO) < 0;
		close(minishell->outfile_fd);
	}
	if (minishell->ispipe)
		close_pipe(minishell->pipe);
	if (dup_failed)
		clean_exit("minishell: dup error", minishell, 0);
}

void	get_path(t_commands *command, t_minishell *minishell)
{
	(void)command;
	(void)minishell;
}

void	execute(t_commands *command, t_minishell *minishell)
{
	setup_fd(command, minishell);
	get_path(command, minishell);
	if (!command->cmd_name)
	{
		ft_dprintf(STDERR_FILENO, "minishell: command not found %s\n",
			command->cmd[0]);
	}
	else if (access(command->cmd_name, F_OK | X_OK) == -1 && errno == ENOENT)
		clean_exit(command->cmd_name, minishell, 127);
	else
	{
		execve(command->cmd_name, command->cmd, minishell->env);
		clean_exit(command->cmd_name, minishell, 126);
	}
	clean_exit(NULL, minishell, 127);
}
