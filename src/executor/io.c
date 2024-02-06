/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:46:50 by aattali           #+#    #+#             */
/*   Updated: 2024/02/06 13:10:25 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief write the text heredoc'ed to the pipe
 *
 * @param eof the eof delimiter
 * @param fd the write end of the pipe
 */
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

/**
 * @brief safely open a file with error handling
 *
 * @param filename the name of the file
 * @param flags the flags given to open
 * @param commands linked-list of commands for error handling
 * @return the fd opened
 */
int	safe_open(char *filename, int flags, t_command *commands)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
		clean_exit(filename, commands);
	return (fd);
}
