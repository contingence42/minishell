/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:05:56 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:42:11 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lex_add_back(t_lexer **list, t_lexer *node, int *err)
{
	t_lexer	*last;

	if (!node || *err)
	{
		*err = 1;
		return ;
	}
	if (!*list)
	{
		*list = node;
		return ;
	}
	last = lex_last(*list);
	node->next = last->next;
	node->before = last;
	last->next = node;
}
