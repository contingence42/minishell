/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:01:58 by aattali           #+#    #+#             */
/*   Updated: 2024/02/20 10:29:47 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief add the cmd array to the linked-list of commands
 *
 * @param command the linked-list of commands
 * @param tmp the cmd splitted into an array of strings
 * @param i incrementer initialised at zero if success
 * @return success or not
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
 * @brief handle every io cases in the parsing
 *
 * TODO: we need to adapt the process because a command
 * can have an arbitrary number of io operations
 *
 * @param node the node of a lexed element
 * @param executor the struct of the exec process
 * @param command the linked-list of commands
 */
int		io_handler(t_lexer *node, t_executor **executor, t_commands **command)
{
	char	*str;

	(void)command;
	if (node->content)
	{
		str = ft_strdup(node->content);
		if (!str)
			return (malloc_error());
	}
	if (node->type == INFILE)
		(*executor)->infn = str;
	else if (node->type == OUTFILE)
		(*executor)->outfn = str;
	else if (node->type == HEREDOC)
	{
		(*executor)->infile = DOUBLE;
		(*executor)->limiter = str;
	}
	else if (node->type == RDR_IN)
		(*executor)->infile = SINGLE;
	else if (node->type == RDR_OUT_T)
		(*executor)->outfile = SINGLE;
	else if (node->type == RDR_OUT_A)
		(*executor)->outfile = DOUBLE;
	return (EXIT_SUCCESS);
}
