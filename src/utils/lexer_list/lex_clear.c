/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:07:02 by aattali           #+#    #+#             */
/*   Updated: 2024/01/30 13:07:15 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_clear(t_lexer **list)
{
	t_lexer	*next;

	if (!list)
		return ;
	while (*list)
	{
		next = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = next;
	}
	*list = NULL;
}
