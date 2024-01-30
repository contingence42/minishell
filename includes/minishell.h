/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:43:59 by kdaumont          #+#    #+#             */
/*   Updated: 2024/01/30 09:59:10 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>

typedef enum e_lextype
{
	UNDEF,
	SQUOTE,
	DQUOTE,
	PIPE,
	HEREDOC,
	RDR_IN,
	RDR_OUT_T,
	RDR_OUT_A,
	INFILE,
	OUTFILE,
	COMMAND
}	t_lextype;

typedef enum e_file
{
	EMPTY,
	SINGLE,
	DOUBLE
}	t_file;

typedef struct s_lexer
{
	char			*content;
	size_t			index;
	t_lextype		type;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_command
{
	char				*cmd_name;
	char				**cmd;
	t_file				infile;
	t_file				outfile;
	int					infile_fd;
	int					outfile_fd;
	bool				pipe;
	bool				builtin;
	struct s_command	*next;
}	t_command;

typedef struct s_minishell
{
	t_command	*command;
	int			saved_stdin;
}	t_minishell;

#endif
