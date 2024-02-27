/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:43:59 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:51:16 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "structs.h"

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <unistd.h>
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

void	handler(char *line, t_minishell *minishell);
int		malloc_error(void);

t_env	*env_new(char *content);
t_env	*env_last(t_env *list);
t_env	*env_get(t_env *list, char *key);
char	**env_collapse(t_env *list);
int		env_add_back(t_env **list, t_env *node);
void	env_clear(t_env **list);

#endif
