/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:43:59 by kdaumont          #+#    #+#             */
/*   Updated: 2024/02/06 12:49:20 by aattali          ###   ########.fr       */
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
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

# define DEFAULT_PATH "/bin:/sbin:/usr/bin:/usr/sbin:\
/usr/local/bin:/usr/local/sbin"
# define MALLOC_ERROR "minishell: malloc error.\n"
# define UNCLOSED_QUOTE_ERROR "minishell: unclosed quotes are forbidden.\n"
# define HD_ERROR "minishell: warning: here-document delimited by end-of-file\
(wanted `"

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
	char		*limiter;
	int			pipe[2];
	int			heredoc[2];
	int			saved_stdin;
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

int		safe_open(char *filename, int flags, t_command *commands);
void	clean_exit(char *s, t_command *commands);
void	write_heredoc(char *eof, int fd);

void	ft_cd(t_command *commands);
void	ft_echo(t_command *commands);
void	ft_pwd(t_command *commands);
void	ft_env(t_command *commands);
void	ft_export(t_command *commands);
void	ft_unset(t_command *commands);
void	ft_exit(t_command *commands);

#endif
