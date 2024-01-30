/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:06:13 by aattali           #+#    #+#             */
/*   Updated: 2024/01/30 13:06:23 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lex_new(char *content)
{
	t_lexer	*node;

	node = ft_calloc(1, sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->before = NULL;
	node->type = UNDEF;
	return (node);
}
