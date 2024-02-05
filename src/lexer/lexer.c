/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:16:42 by aattali           #+#    #+#             */
/*   Updated: 2024/02/02 14:35:36 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief transform a line into a linked list of revelant elements
 *
 * The lexing is done in four phases, that will create a linked-list
 * to be parsed.
 * STEP 1 : Transform the line into a linked-list, with quoted
 * nodes and undef nodes.
 * STEP 2 : Expand the variables inside the nodes that aren't single quoted.
 * Redo step-1 again if there are new quotes given by the expansion.
 * STEP 3 : Find every other separators in UNDEF nodes, 
 * adjusting the nodes if needed, that will be separated by them.
 * STEP 4 : Verify the coherence of the linked-list, check syntax errors.
 *
 * TODO: STEP 2 TO 4
 *
 * @param line the line given by readline
 * @return the linked list of lexed elements
 */
t_lexer	*lexer(char *line)
{
	t_lexer	*list;

	list = handle_quotes(line);
	return (list);
}