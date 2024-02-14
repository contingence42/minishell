/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:00:41 by aattali           #+#    #+#             */
/*   Updated: 2024/02/14 10:03:13 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief exit cleanly the execution process and return to the prompt
 *
 * TODO: everything
 *
 * @param s custom error message
 * @param command the linked-list
 * @param code the exit code
 */
void	clean_exit(char *s, t_minishell *minishell, int code)
{
	if (s)
		perror(s);
	(void)minishell;
	if (code)
		exit(code);
	exit(EXIT_FAILURE);
}

/**
 * @brief handle the preparation of the heredoc pipe
 *
 * @param minishell the general struct
 */
void	handle_heredoc(t_minishell *minishell)
{
	if (pipe(minishell->heredoc) == -1)
		clean_exit("minishell: pipe error", minishell, 0);
	write_heredoc(minishell->limiter, minishell->heredoc[1]);
	close(minishell->heredoc[1]);
}

/**
 * @brief handle the execution of builtins
 *
 * TODO: probably clarify that builtins doesn't accept input and output
 *
 * @param command the linked-list of command
 */
void	handle_builtins(t_commands *command)
{
	if (!ft_strcmp(command->cmd_name, "cd"))
		ft_cd(command);
	else if (!ft_strcmp(command->cmd_name, "echo"))
		ft_echo(command);
	else if (!ft_strcmp(command->cmd_name, "pwd"))
		ft_pwd(command);
	else if (!ft_strcmp(command->cmd_name, "export"))
		ft_export(command);
	else if (!ft_strcmp(command->cmd_name, "unset"))
		ft_unset(command);
	else if (!ft_strcmp(command->cmd_name, "env"))
		ft_env(command);
	else if (!ft_strcmp(command->cmd_name, "exit"))
		ft_exit(command);
}

/**
 * @brief handle the execution process of everything that isn't a builtin
 *
 * setup the pipe if necessary, then fork and execute
 *
 * @param command the linked-list of command
 * @param minishell the general struct
 */
void	handle_forking(t_commands *command, t_minishell *minishell)
{
	if (minishell->ispipe)
	{
		if (pipe(minishell->pipe) == -1)
			clean_exit("minishell: pipe error", minishell, 0);
	}
	minishell->pid = fork();
	if (minishell->pid == -1)
		clean_exit("minishell: fork error", minishell, 0);
	if (!minishell->pid)
		execute(command, minishell);
	if (minishell->ispipe)
	{
		if (!isbroken_pipe(command))
			dup2(minishell->pipe[0], STDIN_FILENO);
		close_pipe(minishell->pipe);
	}
	if (minishell->infile == DOUBLE && command->first)
		close(minishell->heredoc[0]);
}

/**
 * @brief handle the execution of all the command
 *
 * TODO:evertyhing about the structs need to be clarified,
 * which variables will be in the linked-list, which will be in the struct, etc
 *
 * @param minishell the general struct of the program
 */
void	the_executor(t_minishell *minishell)
{
	t_commands	*command;

	command = minishell->command;
	minishell->saved_stdin = dup(STDIN_FILENO);
	while (command)
	{
		if (command->first && minishell->infile == DOUBLE && !command->builtin)
			handle_heredoc(minishell);
		if (command->builtin)
			handle_builtins(command);
		else
			handle_forking(command, minishell);
		command = command->next;
	}
}
