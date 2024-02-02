/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:15:46 by aattali           #+#    #+#             */
/*   Updated: 2024/02/02 11:32:31 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief add the substrings into the revelant nodes inside the linked-list
 *
 * @param list the linked-list
 * @param line the line given by readline
 * @param sepend the separator and the position of the paired separator
 * @param pack two iterators packed inside an array
 */
void	add_lex_quotes(t_lexer **list, char *line, int *sepend, size_t *pack[2])
{
	char	*substr;

	if (sepend[0])
	{
		lex_add_back(list, lex_new(ft_substr(line, *pack[1], *pack[0]
					- *pack[1]), UNDEF));
		substr = ft_substr(line, *pack[0] + 1, sepend[1] - 1);
		if (sepend[0] == '"')
			lex_add_back(list, lex_new(substr, DQUOTE));
		else if (sepend[0] == '\'')
			lex_add_back(list, lex_new(substr, SQUOTE));
		*pack[0] += sepend[1];
		*pack[1] = *pack[0] + 1;
	}
	else
		lex_add_back(list, lex_new(line + *pack[0], UNDEF));
	free(sepend);
}

/**
 * @brief iterate over the line and create the linked-list
 *
 * TODO: Error handling if malloc fail or the quote is unclosed
 *
 * @param list the linked-list to be created
 * @param line the line given by readline
 */
void	loop_quotes(t_lexer **list, char *line)
{
	int		*sepend;
	size_t	i;
	size_t	k;
	size_t	*pack[2];

	i = -1;
	k = 0;
	while (line[++i])
	{
		sepend = get_sepend(line + i, "'\"");
		if (!sepend || sepend[1] == -1)
			printf("error\n"); // TODO
		pack[0] = &i;
		pack[1] = &k;
		if (sepend[0] && sepend[1] != -1)
			add_lex_quotes(list, line, sepend, pack);
		else if (!ft_strchr(line + i, '"') && !ft_strchr(line + i, '\''))
		{
			add_lex_quotes(list, line, sepend, pack);
			break ;
		}
	}
}

/**
 * @brief transform the line into a linked-list, lexing the quotes
 *
 * TODO: Error handling
 *
 * @param line the line given by readline, which will be freed
 * @return the linked-list with UNDEF nodes and DQUOTE/SQUOTE nodes
 */
t_lexer	*handle_quotes(char *line)
{
	t_lexer	*list;

	loop_quotes(&list, line);
	free(line);
	return (list);
}
