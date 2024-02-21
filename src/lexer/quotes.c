/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:15:46 by aattali           #+#    #+#             */
/*   Updated: 2024/02/21 14:04:10 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief give the position of the paired separator
 *
 * @param str the string to search, the pointer is at the first separator
 * @param c the separator
 * @return the position of the paired separator, or -1 if not found
 */
int	get_sepend(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (-1);
	else
		return (i);
}

/**
 * @brief add the substrings into the revelant nodes inside the linked-list
 *
 * @param list the linked-list
 * @param line the line given by readline
 * @param sepend the position of the paired separator
 * @param pack three iterators and the error code packed inside an array
 */
void	add_lex_quotes(t_lexer **list, char *line, int sepend, int pack[4])
{
	char	*substr;
	int		err;

	err = 0;
	lex_add_back(list, lex_new(ft_substr(line, pack[1], pack[0]
				- pack[1]), UNDEF), &err);
	substr = ft_substr(line, pack[0] + 1, sepend - 1);
	if (pack[2] == '"')
		lex_add_back(list, lex_new(substr, DQUOTE), &err);
	else if (pack[2] == '\'')
		lex_add_back(list, lex_new(substr, SQUOTE), &err);
	pack[0] += sepend;
	pack[1] = pack[0] + 1;
	pack[3] = err;
}

/**
 * @brief iterate over the line and create the linked-list
 *
 * pack[0] = i, standard iterator over string
 * pack[1] = k, initial position of the start of the substr
 * pack[2] = c, separator
 * pack[3] = error flag for malloc error toggled by add_back
 *
 * @param list the linked-list to be created
 * @param line the line given by readline
 * @return error code, 0 good, 1 malloc err, 2 unclosed quote err
 */
int	loop_quotes(t_lexer **list, char *line)
{
	int		c;
	int		sepend;
	int		pack[4];

	pack[0] = -1;
	pack[1] = 0;
	while (line[++pack[0]])
	{
		c = ft_getinset(line[pack[0]], "'\"");
		if (c != -1)
		{
			sepend = get_sepend(line + pack[0], c);
			if (sepend == -1)
				return (2);
			pack[2] = c;
			add_lex_quotes(list, line, sepend, pack);
		}
		else if (!ft_strchr(line + pack[0], '"') && !ft_strchr(line + pack[0],
				'\''))
		{
			lex_add_back(list, lex_new(line + pack[0], UNDEF), &pack[3]);
			break ;
		}
	}
	return (pack[3]);
}

/**
 * @brief call the lexer for the quotes and check for the errors
 *
 * @param line the line given by readline, which will be freed
 * @return the linked-list with UNDEF nodes and DQUOTE/SQUOTE nodes
 */
t_lexer	*handle_quotes(char *line)
{
	t_lexer	*list;
	int		err;

	list = NULL;
	err = loop_quotes(&list, line);
	if (!err && !lex_malloc_check(list))
		err = 1;
	if (err)
	{
		if (err == 1)
			ft_dprintf(STDERR_FILENO, MALLOC_ERROR);
		else
			ft_dprintf(STDERR_FILENO, UNCLOSED_QUOTE_ERROR);
		lex_clear(&list);
	}
	free(line);
	return (list);
}
