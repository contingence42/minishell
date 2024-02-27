/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_add_before.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:07:53 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:43:34 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lex_add_before(t_lexer *list, t_lexer *node)
{
	if (!node || !list)
		return ;
	node->next = list;
	list->before->next = node;
	node->before = list->before;
	list->before = node;
}
