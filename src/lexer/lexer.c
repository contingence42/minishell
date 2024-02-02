/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:16:42 by aattali           #+#    #+#             */
/*   Updated: 2024/02/02 11:24:42 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief find separators and get the pos of the second member
 *
 * Check if the first character of a string is a searched separator.
 * If the separator is paired, the function will obtain the position
 * of the second separator.
 * This function is called inside a loop for every chracter of a string.
 *
 * @param str the string given to search, generally offseted
 * @param seps the separators that are searched
 * @return the separator found and the position of the second member if paired
 */
int	*get_sepend(char *str, char *seps)
{
	int		*result;
	char	c;
	size_t	i;

	result = ft_calloc(2, sizeof(int));
	if (!result)
		return (NULL);
	if (ft_inset(str[0], seps))
	{
		c = str[0];
		if (c == '"' || c == '\'')
		{
			i = 1;
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
				result[1] = -1;
			else
				result[1] = i;
		}
		result[0] = c;
	}
	return (result);
}

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
