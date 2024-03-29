/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:16:42 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:41:09 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

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
 * TODO: STEP 4
 *
 * @param line the line given by readline
 * @param minishell the general struct of the program
 * @return the linked list of lexed elements
 */
t_lexer	*lexer(char *line, t_minishell *minishell)
{
	t_lexer	*list;

	list = handle_quotes(line);
	if (!list)
		return (NULL);
	if (handle_expansion(&list, minishell) == EXIT_FAILURE)
		return (lex_clear(&list), NULL);
	if (handle_separators(&list) == EXIT_FAILURE)
		return (lex_clear(&list), NULL);
	if (handle_cmdio(&list) == EXIT_FAILURE)
		return (lex_clear(&list), NULL);
	return (list);
}
