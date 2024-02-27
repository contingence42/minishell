/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:38:03 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 09:10:24 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lex_delone(t_lexer **list, t_lexer *node)
{
	if (!*list)
		return ;
	if (!node->next && !node->before)
		*list = NULL;
	if (node->before)
		node->before->next = node->next;
	if (node->next)
	{
		node->next->before = node->before;
		if (!node->before)
			*list = node->next;
	}
	free(node->content);
	free(node);
}

static bool	to_trim(t_lextype type)
{
	return (type != DQUOTE && type != SQUOTE && type != DOLLAR);
}

void	lex_trim(t_lexer **list, int *err)
{
	t_lexer	*node;
	char	*tmp;

	if (!*list)
		return ;
	node = *list;
	while (node && !*err)
	{
		if (!node->content || !to_trim(node->type))
		{
			node = node->next;
			continue ;
		}
		tmp = ft_strtrim(node->content, " ");
		if (!tmp)
			*err = 1;
		if (!tmp[0])
		{
			lex_delone(list, node);
			free(tmp);
		}
		else
		{
			free(node->content);
			node->content = tmp;
		}
		node = node->next;
	}
}
