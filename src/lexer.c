/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:16:42 by aattali           #+#    #+#             */
/*   Updated: 2024/02/01 10:01:58 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_quotes(t_lexer **list, char *line)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	c;

	i = -1;
	k = 0;
	while (line[++i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			c = line[i];
			j = 1;
			while (line[i + j] && line[i + j] != c)
				j++;
			if (!line[i + j])
				printf("error quotes parsing"); // TODO handle correctly;
			lex_add_back(list, lex_new(ft_substr(line, k, i - k), UNDEF));
			lex_add_back(list, lex_new(ft_substr(line, i + 1, j - 1), UNDEF));
			i += j;
			k = i + 1;
		}
		else if (!ft_strchr(line + i, '"') && !ft_strchr(line + i, '\''))
		{
			lex_add_back(list, lex_new(ft_strdup(line + i), UNDEF));
			break ;
		}
	}
}

t_lexer	*handle_quotes(char *line)
{
	t_lexer	*list;

	loop_quotes(&list, line);
	if (!list)
		lex_add_back(&list, lex_new(ft_strdup(line), UNDEF));
	free(line);
	return (list);
}
