/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:01:58 by aattali           #+#    #+#             */
/*   Updated: 2024/02/20 09:39:54 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief handle every io cases in the parsing
 *
 * TODO: error handling, and we need to adapt the process because a command
 * can have an arbitrary number of io operations
 *
 * @param node the node of a lexed element
 * @param executor the struct of the exec process
 * @param command the linked-list of commands
 */
void	io_handler(t_lexer *node, t_executor **executor, t_commands **command)
{
	char	*str;

	(void)command;
	if (node->content)
	{
		str = ft_strdup(node->content);
		if (!str)
			return ;
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
}
