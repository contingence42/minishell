/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_geti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:06:40 by aattali           #+#    #+#             */
/*   Updated: 2024/01/30 13:06:47 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lex_geti(t_lexer *list, size_t index)
{
	while (list)
	{
		if (list->index == index)
			return (list);
		list = list->next;
	}
	return (NULL);
}

