/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:43:59 by kdaumont          #+#    #+#             */
/*   Updated: 2024/02/15 09:26:42 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

# define DEFAULT_PATH "/bin:/sbin:/usr/bin:/usr/sbin:\
/usr/local/bin:/usr/local/sbin"
# define MALLOC_ERROR "minishell: malloc error.\n"
# define PIPE_ERROR "minishell: pipe error.\n"
# define FORK_ERROR "minishell: fork error.\n"
# define DUP_ERROR "minishell: dup error.\n"
# define UNCLOSED_QUOTE_ERROR "minishell: unclosed quotes are forbidden.\n"
# define HD_ERROR "minishell: warning: here-document delimited by end-of-file\
(wanted `"
# define CMD_NOT_FOUND "minishell: command not found %s\n"

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

typedef struct s_executor
{
	pid_t		pid;
	t_file		infile;
	t_file		outfile;
	bool		ispipe;
	char		***env;
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
	char	**env;
}	t_minishell;

bool	lex_malloc_check(t_lexer *list);
void	lex_clear(t_lexer **list);
void	lex_add_back(t_lexer **list, t_lexer *node);
void	lex_add_before(t_lexer *list, t_lexer *node);
void	lex_add_after(t_lexer **list, t_lexer *node);
t_lexer	*lex_new(char *content, t_lextype type);
t_lexer	*lex_geti(t_lexer *list, size_t index);
t_lexer	*lex_last(t_lexer *list);
t_lexer	*lexer(char *line);
t_lexer	*handle_quotes(char *line);

bool	isbroken_pipe(t_commands *command);
int		safe_open(t_executor *executor, int flag);
int		wait_childs(t_executor *executor);
void	close_pipe(int pipe[2]);
void	execute(t_commands *command, t_executor *executor);
void	clean_exit(char *s, t_executor *executor, int code);
void	find_path(t_executor *executor);
void	write_heredoc(char *eof, int fd);

void	ft_cd(t_commands *command);
void	ft_echo(t_commands *command);
void	ft_pwd(t_commands *command);
void	ft_env(t_commands *command);
void	ft_export(t_commands *command);
void	ft_unset(t_commands *command);
void	ft_exit(t_commands *command);

#endif
