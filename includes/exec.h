/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:48:37 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:49:02 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

bool	isbroken_pipe(t_commands *command);
int		safe_open(t_executor *executor, int flag);
int		wait_childs(t_executor *executor);
int		get_env_pos(char **env, char *key);
void	close_pipe(int pipe[2]);
void	execute(t_commands *command, t_executor *executor);
void	clean_exit(char *s, t_executor *executor, int code);
void	find_path(t_executor *executor);
void	write_heredoc(char *eof, int fd);
int		the_executor(t_executor *executor, t_commands *command);

void	ft_cd(t_commands *command);
void	ft_echo(t_commands *command);
void	ft_pwd(t_commands *command);
void	ft_env(t_executor *executor);
void	ft_export(t_executor *executor, t_commands *command);
void	ft_unset(t_executor *executor, t_commands *command);
void	ft_exit(t_commands *command);

#endif
