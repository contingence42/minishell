/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:44:45 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:45:27 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

int			parser(t_lexer *lex, t_executor **executor, t_commands **command);
int			io_handler(t_lexer **node, t_executor *executor,
				t_commands **command);
int			pipe_handler(t_executor *exec, t_commands **cmd, char ***tmp,
				int *i);
int			push_cmd(t_commands **command, char ***tmp, int *i);
int			cmd_add_back(t_commands **command, t_commands *node);
void		cmd_clear(t_commands **cmd);
t_commands	*cmd_new(char	**content);

#endif
