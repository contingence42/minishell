/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_add_after.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:08:15 by aattali           #+#    #+#             */
/*   Updated: 2024/02/20 12:48:55 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_add_after(t_lexer **list, t_lexer *node, int *err)
{
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
	node->next = (*list)->next;
	node->before = *list;
	(*list)->next = node;
}
