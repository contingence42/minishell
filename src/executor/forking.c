/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:57:20 by aattali           #+#    #+#             */
/*   Updated: 2024/02/21 11:23:03 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief wait for all of the childs and return the latest error code
 *
 * TODO: adapt to executor, is the errcode useful ?
 *
 * @param executor the struct of the program
 * @return the error code
 */
int	wait_childs(t_executor *executor)
{
	int	wstatus;
	int	code;

	code = EXIT_FAILURE;
	while (errno != ECHILD)
	{
		if (wait(&wstatus) == executor->pid)
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
 * @param command the linked list of commands
 * @param executor the struct of the exec process
 */
void	setup_fd(t_commands *command, t_executor *executor)
{
	bool	dup_failed;

	dup_failed = false;
	if (command->first && executor->infile != EMPTY)
	{
		if (executor->infile == DOUBLE)
			executor->infile_fd = executor->heredoc[0];
		else
			executor->infile_fd = safe_open(executor, 0);
		dup_failed |= dup2(executor->infile_fd, STDIN_FILENO) < 0;
		close(executor->infile_fd);
	}
	if (!command->last && executor->ispipe)
		dup_failed |= dup2(executor->pipe[1], STDOUT_FILENO) < 0;
	else if (executor->outfile != EMPTY)
	{
		executor->outfile_fd = safe_open(executor, 1);
		dup_failed |= dup2(executor->outfile_fd, STDOUT_FILENO) < 0;
		close(executor->outfile_fd);
	}
	if (executor->ispipe)
		close_pipe(executor->pipe);
	if (dup_failed)
		clean_exit(DUP_ERROR, executor, 0);
}

/**
 * @brief replace cmd_name with the full and correct path
 *
 * @param command the linked-list of commands
 * @param executor the struct of the exec process
 */
int	get_path(t_commands *command, t_executor *executor)
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
	while (executor->path && executor->path[++i])
	{
		cmdpath = ft_strjoin3(executor->path[i], "/", cmd);
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
 * @param executor the struct of the exec process
 */
void	execute(t_commands *command, t_executor *executor)
{
	char	**env;

	setup_fd(command, executor);
	if (get_path(command, executor) == -1)
		clean_exit(MALLOC_ERROR, executor, 0);
	if (!command->cmd_name)
	{
		ft_dprintf(STDERR_FILENO, CMD_NOT_FOUND,
			command->cmd[0]);
	}
	else if (access(command->cmd_name, F_OK | X_OK) == -1 && errno == ENOENT)
		clean_exit(command->cmd_name, executor, 127);
	else
	{
		env = env_collapse(*(executor->env));
		execve(command->cmd_name, command->cmd, env);
		ft_free_astr(env);
		clean_exit(command->cmd_name, executor, 126);
	}
	clean_exit(NULL, executor, 127);
}
