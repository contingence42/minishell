/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:46:50 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:49:56 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

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
 * @param executor the struct of the exec process
 * @param flag 0 if infile, 1 if outfile
 * @return the fd opened
 */
int	safe_open(t_executor *executor, int flag)
{
	int		fd;
	int		flags;
	char	*filename;

	if (!flag)
	{
		flags = O_RDONLY;
		filename = executor->infn;
	}
	else
	{
		if (executor->outfile == SINGLE)
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		else
			flags = O_WRONLY | O_CREAT | O_APPEND;
		filename = executor->outfn;
	}
	fd = open(filename, flags, 0644);
	if (fd == -1)
		clean_exit(filename, executor, 0);
	return (fd);
}
