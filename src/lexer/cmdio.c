/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:12:13 by aattali           #+#    #+#             */
/*   Updated: 2024/02/26 14:54:43 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_lex(t_lexer *list, char **split, int *err)
{
	int	i;

	free(list->content);
	list->content = ft_strdup(split[0]);
	list->type = COMMAND;
	if (!list->content)
		*err = 1;
	i = 0;
	while (!*err && split && split[++i])
	{
		lex_add_after(&list, lex_new(ft_strdup(split[i]), COMMAND), err);
		list = list->next;
	}
	ft_free_astr(split);
}

static int	splitter(t_lexer *list)
{
	char	**tmp;
	int		err;

	err = 0;
	while (list && !err)
	{
		if (list->type == UNDEF)
		{
			if (ft_strchrpos(list->content, ' ') == -1)
			{
				list->type = COMMAND;
				list = list->next;
				continue ;
			}
			tmp = ft_split(list->content, ' ');
			if (!tmp)
				return (1);
			update_lex(list, tmp, &err);
		}
		list = list->next;
	}
	return (err);
}

static void	rename_iofiles(t_lexer *list)
{
	while (list)
	{
		if ((list->type == HEREDOC || list->type == RDR_IN) && list->next)
			list->next->type = INFILE;
		else if ((list->type == RDR_OUT_T || list->type == RDR_OUT_A)
			&& list->next)
			list->next->type = OUTFILE;
		list = list->next;
	}
}

int	handle_cmdio(t_lexer **list)
{
	int	err;

	err = splitter(*list);
	if (err)
		return (malloc_error());
	rename_iofiles(*list);
	return (EXIT_SUCCESS);
}
