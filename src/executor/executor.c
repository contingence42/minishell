/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:00:41 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:49:41 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/**
 * @brief exit cleanly the execution process and return to the prompt
 *
 * TODO: everything
 *
 * @param s custom error message
 * @param command the linked-list
 * @param code the exit code
 */
void	clean_exit(char *s, t_executor *executor, int code)
{
	if (s)
		perror(s);
	(void)executor;
	if (code)
		exit(code);
	exit(EXIT_FAILURE);
}

/**
 * @brief handle the preparation of the heredoc pipe
 *
 * @param executor the struct of the exec process
 */
void	handle_heredoc(t_executor *executor)
{
	if (pipe(executor->heredoc) == -1)
		clean_exit(PIPE_ERROR, executor, 0);
	write_heredoc(executor->limiter, executor->heredoc[1]);
	close(executor->heredoc[1]);
}

/**
 * @brief handle the execution of builtins
 *
 * TODO: probably clarify that builtins doesn't accept input and output
 *
 * @param command the linked-list of commands
 */
void	handle_builtins(t_executor *executor, t_commands *command)
{
	if (!ft_strcmp(command->cmd_name, "cd"))
		ft_cd(command);
	else if (!ft_strcmp(command->cmd_name, "echo"))
		ft_echo(command);
	else if (!ft_strcmp(command->cmd_name, "pwd"))
		ft_pwd(command);
	else if (!ft_strcmp(command->cmd_name, "export"))
		ft_export(executor, command);
	else if (!ft_strcmp(command->cmd_name, "unset"))
		ft_unset(executor, command);
	else if (!ft_strcmp(command->cmd_name, "env"))
		ft_env(executor);
	else if (!ft_strcmp(command->cmd_name, "exit"))
		ft_exit(command);
}

/**
 * @brief handle the execution process of everything that isn't a builtin
 *
 * setup the pipe if necessary, then fork and execute
 *
 * @param command the linked-list of commands
 * @param executor the struct of the exec process
 */
void	handle_forking(t_commands *command, t_executor *executor)
{
	if (executor->ispipe)
	{
		if (pipe(executor->pipe) == -1)
			clean_exit(PIPE_ERROR, executor, 0);
	}
	executor->pid = fork();
	if (executor->pid == -1)
		clean_exit(FORK_ERROR, executor, 0);
	if (!executor->pid)
		execute(command, executor);
	if (executor->ispipe)
	{
		if (!isbroken_pipe(command))
			dup2(executor->pipe[0], STDIN_FILENO);
		close_pipe(executor->pipe);
	}
	if (executor->infile == DOUBLE && command->first)
		close(executor->heredoc[0]);
}

/**
 * @brief handle the execution of all the command
 *
 * @param executor the struct of the exec process
 * @param command the linked-list of commands
 */
int	the_executor(t_executor *executor, t_commands *command)
{
	executor->saved_stdin = dup(STDIN_FILENO);
	find_path(executor);
	while (command)
	{
		if (command->first && executor->infile == DOUBLE && !command->builtin)
			handle_heredoc(executor);
		if (command->builtin)
			handle_builtins(executor, command);
		else
			handle_forking(command, executor);
		command = command->next;
	}
	dup2(executor->saved_stdin, STDIN_FILENO);
	close(executor->saved_stdin);
	return (wait_childs(executor));
}
