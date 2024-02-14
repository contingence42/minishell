/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:57:20 by aattali           #+#    #+#             */
/*   Updated: 2024/02/14 13:20:06 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief wait for all of the childs and return the latest error code
 *
 * TODO: adapt to minishell, is the errcode useful ?
 *
 * @param minishell the struct of the program
 * @return the error code
 */
int	wait_childs(t_minishell *minishell)
{
	int	wstatus;
	int	code;

	code = EXIT_FAILURE;
	while (errno != ECHILD)
	{
		if (wait(&wstatus) == minishell->pid)
		{
			if (WIFEXITED(wstatus))
				code = WEXITSTATUS(wstatus);
			else
				code = 128 + WTERMSIG(wstatus);
		}
	}
	return (code);
}

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

/**
 * @brief replace cmd_name with the full and correct path
 *
 * @param command the linked-list of commands
 * @param minishell the struct of the program
 */
int	get_path(t_commands *command, t_minishell *minishell)
{
	size_t	i;
	char	*cmd;
	char	*cmdpath;

	cmd = command->cmd_name;
	if (!cmd || !ft_strcmp(cmd, "."))
		return (command->cmd_name = NULL, 0);
	if (ft_strchr(cmd, '/'))
		return (command->cmd_name = ft_strdup(cmd),
			(command->cmd_name != NULL) - 1);
	i = -1;
	while (minishell->path && minishell->path[++i])
	{
		cmdpath = ft_strjoin3(minishell->path[i], "/", cmd);
		if (!cmdpath)
			return (-1);
		if (!access(cmdpath, F_OK | X_OK))
			return (command->cmd_name = cmdpath, 0);
		free(cmdpath);
	}
	return (0);
}

/**
 * @brief execute the command via execve, handling errors and pipes
 *
 * @param command the linked-list of commands
 * @param minishell the struct of the program
 */
void	execute(t_commands *command, t_minishell *minishell)
{
	setup_fd(command, minishell);
	if (get_path(command, minishell) == -1)
		clean_exit("minishell: mem error", minishell, 0);
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
