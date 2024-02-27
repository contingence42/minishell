/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:01:58 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:46:09 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/**
 * @brief check if the node is a io associated type
 *
 * @param type the type of the node
 * @return boolean
 */
static bool	is_io(t_lextype type)
{
	return (type == HEREDOC || type == RDR_IN || type == RDR_OUT_T
		|| type == RDR_OUT_A || type == INFILE || type == OUTFILE);
}

/**
 * @brief add the cmd array to the linked-list of commands
 *
 * @param command the linked-list of commands
 * @param tmp the cmd splitted into an array of strings
 * @param i incrementer initialised at zero if success
 * @return error code in case of malloc errors
 */
int	push_cmd(t_commands **command, char ***tmp, int *i)
{
	if (cmd_add_back(command, cmd_new(*tmp)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*tmp = NULL;
	*i = 0;
	return (EXIT_SUCCESS);
}

/**
 * @brief toggle the flag in exec structure and push cmds into the linked-list
 *
 * @param exec the struct of the exec process
 * @param cmd the linked-list of commands
 * @param tmp the cmd splitted into an array of strings
 * @param i incrementer given to push_cmd
 * @return error code in case of malloc errors
 */
int	pipe_handler(t_executor *exec, t_commands **cmd, char ***tmp, int *i)
{
	exec->ispipe = true;
	if (push_cmd(cmd, tmp, i) == EXIT_FAILURE)
		return (ft_free_astr(*tmp), malloc_error());
	return (0);
}

/**
 * @brief toggle the corresponding flags inside the exec struct
 *
 * @param node the node of a lexed element
 * @param exec the struct of the exec process
 * @param cmd the linked-list of commands
 * @param str a malloc'd string for filename
 * @return 0 if the node is not io, 1 if it is
 */
static int	io_sl(t_lexer *node, t_executor *exec, t_commands **cmd, char *str)
{
	(void)cmd;
	if (node->type == INFILE)
		exec->infn = str;
	else if (node->type == OUTFILE)
		exec->outfn = str;
	else if (node->type == HEREDOC)
	{
		exec->infile = DOUBLE;
		exec->limiter = str;
	}
	else if (node->type == RDR_IN)
		exec->infile = SINGLE;
	else if (node->type == RDR_OUT_T)
		exec->outfile = SINGLE;
	else if (node->type == RDR_OUT_A)
		exec->outfile = DOUBLE;
	else
		return (0);
	return (1);
}

/**
 * @brief handle every io cases in the parsing
 *
 * TODO: we need to adapt the process because a command
 * can have an arbitrary number of io operations
 *
 * @param node the node of a lexed element
 * @param executor the struct of the exec process
 * @param command the linked-list of commands
 * @return error code in case of malloc errors
 */
int	io_handler(t_lexer **node, t_executor *executor, t_commands **command)
{
	char	*str;

	while (*node && is_io((*node)->type))
	{
		if ((*node)->content)
		{
			str = ft_strdup((*node)->content);
			if (!str)
				return (malloc_error());
		}
		if (!io_sl(*node, executor, command, str))
			return (EXIT_SUCCESS);
		if (!(*node)->next)
			break ;
		*node = (*node)->next;
	}
	return (EXIT_SUCCESS);
}
