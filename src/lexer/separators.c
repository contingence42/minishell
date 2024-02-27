/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:39:50 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:41:21 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

/**
 * @brief get the pos of the separator
 *
 * @param str the string to be searched
 * @return the position, or -1 if missing
 */
static int	get_separator(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
			return (i);
		if (str[i] == '>')
			return (i);
		if (str[i] == '<')
			return (i);
	}
	return (-1);
}

/**
 * @brief get the position of the double separator if it exists
 *
 * @param str the string to be searched
 * @param pos_s the position of the first separator
 * @return the position of the second pair, or -1 if missing
 */
static int	get_end(char *str, int pos_s)
{
	if (str[pos_s + 1] && str[pos_s] == str[pos_s + 1])
		return (pos_s + 1);
	else
		return (-1);
}

/**
 * @brief update the linked-list to create the needed nodes
 *
 * @param node the node to be separated
 * @param pos_s the position of the separator
 * @param pos_e the position of the double sep, or -1 if missing
 * @param err the error code that will be toggled if there's a malloc error
 */
static void	update_lex(t_lexer *node, int pos_s, int pos_e, int *err)
{
	int		len;
	char	*content;

	content = node->content;
	len = ft_strlen(content);
	if (pos_e == -1)
	{
		lex_add_after(&node, lex_new(NULL, get_lextype(content[pos_s], 0)),
			err);
		pos_e = pos_s;
	}
	else
		lex_add_after(&node, lex_new(NULL, get_lextype(content[pos_s], 1)),
			err);
	lex_add_after(&node->next, lex_new(ft_substr(content, pos_e + 1, len),
			UNDEF), err);
	node->content = ft_substr(content, 0, pos_s);
	if (!node->content)
		*err = 1;
	free(content);
}

/**
 * @brief create new nodes containing the separators between UNDEF nodes
 *
 * @param list the linked-list of lexed elements
 * @return error code in case of malloc errors
 */
static int	separate(t_lexer *list)
{
	int		pos_s;
	int		pos_e;
	int		err;

	err = 0;
	while (list && !err)
	{
		if (list->type == UNDEF)
		{
			pos_s = get_separator(list->content);
			if (pos_s == -1)
			{
				list = list->next;
				continue ;
			}
			pos_e = get_end(list->content, pos_s);
			update_lex(list, pos_s, pos_e, &err);
		}
		list = list->next;
	}
	return (err);
}

/**
 * @brief separate the linked-list with the seps
 *
 * @param list the linked-list of lexed elements
 * @return error code in case of malloc errors
 */
int	handle_separators(t_lexer **list)
{
	int	err;

	err = separate(*list);
	lex_trim(list, &err);
	if (err)
		return (malloc_error());
	return (EXIT_SUCCESS);
}
