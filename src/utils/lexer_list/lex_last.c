/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:07:31 by aattali           #+#    #+#             */
/*   Updated: 2024/01/30 13:07:38 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lex_last(t_lexer *list)
{
	if (list)
		while (list)
			list = list->next;
	return (list);
}
