/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:00:41 by aattali           #+#    #+#             */
/*   Updated: 2024/02/05 10:53:20 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(char *s, t_command *commands)
{

}

void	write_heredoc(char *eof, int fd)
{
	char	*line;
	size_t	len;

	len = ft_strlen(eof);
	while (true)
	{
		printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, "%s%s')\n", HD_ERROR, eof);
			break ;
		}
		if (!ft_strncmp(line, eof, len) && line[len] == '\n')
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
}

int	safe_open(char *filename, int flags, t_command *commands)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
		clean_exit(filename, commands);
	return (fd);
}

void	handle_heredoc(t_command *commands);
void	handle_builtins(t_command *commands);
void	handle_forking(t_command *commands);

void	the_executor(t_minishell *minishell)
{
	t_command	*commands;

	commands = minishell->command;
	minishell->saved_stdin = dup(STDIN_FILENO);
	while (commands)
	{
		if (commands->infile == HEREDOC)
			handle_heredoc(commands);
		if (commands->builtin)
			handle_builtins(commands);
		else
			handle_forking(commands);
		commands = commands->next;
	}
}
