/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:36:27 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:38:31 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <unistd.h>

typedef enum e_lextype
{
	UNDEF,
	SQUOTE,
	DQUOTE,
	DOLLAR,
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
	t_lextype		type;
	struct s_lexer	*before;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_commands
{
	char				*cmd_name;
	char				**cmd;
	bool				builtin;
	bool				first;
	bool				last;
	struct s_commands	*next;
}	t_commands;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*before;
	struct s_env	*next;
}	t_env;

typedef struct s_executor
{
	pid_t		pid;
	t_file		infile;
	t_file		outfile;
	t_env		**env;
	bool		ispipe;
	char		**path;
	char		*limiter;
	char		*infn;
	char		*outfn;
	int			pipe[2];
	int			heredoc[2];
	int			infile_fd;
	int			outfile_fd;
	int			saved_stdin;
}	t_executor;

typedef struct s_minishell
{
	t_env	*env;
	int		code;
}	t_minishell;

#endif
