/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:00:41 by aattali           #+#    #+#             */
/*   Updated: 2024/02/06 13:15:34 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief exit cleanly the execution process and return to the prompt
 *
 * TODO: everything
 *
 * @param s custom error message
 * @param commands the linked-list
 */
void	clean_exit(char *s, t_command *commands)
{
	(void)s;
	(void)commands;
}

/**
 * @brief handle the preparation of the heredoc pipe
 *
 * @param minishell the general struct
 */
void	handle_heredoc(t_minishell *minishell)
{
	if (pipe(minishell->heredoc) == -1)
		clean_exit(NULL, minishell->command);
	write_heredoc(minishell->limiter, minishell->heredoc[1]);
	close(minishell->heredoc[1]);
}

/**
 * @brief handle the execution of builtins
 *
 * TODO: probably clarify that builtins doesn't accept input and output
 *
 * @param commands the linked-list of commands
 */
void	handle_builtins(t_command *commands)
{
	if (!ft_strcmp(commands->cmd_name, "cd"))
		ft_cd(commands);
	else if (!ft_strcmp(commands->cmd_name, "echo"))
		ft_echo(commands);
	else if (!ft_strcmp(commands->cmd_name, "pwd"))
		ft_pwd(commands);
	else if (!ft_strcmp(commands->cmd_name, "export"))
		ft_export(commands);
	else if (!ft_strcmp(commands->cmd_name, "unset"))
		ft_unset(commands);
	else if (!ft_strcmp(commands->cmd_name, "env"))
		ft_env(commands);
	else if (!ft_strcmp(commands->cmd_name, "exit"))
		ft_exit(commands);
}

/**
 * @brief handle the execution process of everything that isn't a builtin
 *
 * TODO:everything, there's just a simple and unfinished prototype
 *
 * @param commands the linked-list of commands
 * @param minishell the general struct
 */
void	handle_forking(t_command *commands, t_minishell *minishell)
{
	if (commands->pipe)
	{
		if (pipe(minishell->pipe) == -1)
			clean_exit(NULL, commands);
	}
}

/**
 * @brief handle the execution of all the commands
 *
 * TODO:evertyhing about the structs need to be clarified,
 * which variables will be in the linked-list, which will be in the struct, etc
 *
 * @param minishell the general struct of the program
 */
void	the_executor(t_minishell *minishell)
{
	t_command	*commands;

	commands = minishell->command;
	minishell->saved_stdin = dup(STDIN_FILENO);
	while (commands)
	{
		if (commands->infile == HEREDOC && !commands->builtin)
			handle_heredoc(minishell);
		if (commands->builtin)
			handle_builtins(commands);
		else
			handle_forking(commands, minishell);
		commands = commands->next;
	}
}
