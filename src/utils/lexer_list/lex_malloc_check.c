/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_malloc_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:10:42 by aattali           #+#    #+#             */
/*   Updated: 2024/02/02 14:40:10 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	lex_malloc_check(t_lexer *list)
{
	while (list->next)
	{
		if (!list->content && (list->type == COMMAND || list->type == DQUOTE
				|| list->type == SQUOTE || list->type == UNDEF))
			return (false);
		list = list->next;
	}
	return (true);
}
