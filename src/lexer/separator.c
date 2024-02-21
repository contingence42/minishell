/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:03:49 by kdaumont          #+#    #+#             */
/*   Updated: 2024/02/21 14:01:39 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if there are a separator in the content
@param content -> the content to check
@return the type of separator or 0 if none
*/
int	check_separator(char *content)
{
	if (!content)
		return (0);
	if (ft_strnstr(content, ">>", ft_strlen(content)))
		return (RDR_OUT_A);
	else if (ft_strnstr(content, ">", ft_strlen(content)))
		return (RDR_OUT_T);
	else if (ft_strnstr(content, "<", ft_strlen(content)))
		return (RDR_IN);
	else if (ft_strnstr(content, "<<", ft_strlen(content)))
		return (HEREDOC);
	else if (ft_strnstr(content, "|", ft_strlen(content)))
		return (PIPE);
	return (0);
}

/* Get all flags for a command
@param splited -> command str split
@param j -> last index
@return all name str
*/
char	*get_flags_name(char **splited, int j)
{
	char *tmp;

	tmp = "";
	while (splited[j] && !check_separator(splited[j]))
	{
		tmp = ft_strjoin3(tmp, " ", splited[j]);
		j++;
	}
	return (tmp);
}

/* Create fine nodes for the command list
@param splited -> command str split
@param count -> amount of fine nodes
@param list -> new list
*/
void	create_separators_nodes(char **splited, int count, t_lexer **list)
{
	int		i;
	int		j;
	t_lexer	*new;

	i = -1;
	j = 0;
	while (++i < count)
	{
		if (splited[j])
		{
			new = lex_new(get_flags_name(splited, j), COMMAND);
			lex_add_back(list, new, 0);
		}
		while (splited[j] && !check_separator(splited[j]))
			j++;
		if (splited[j])
		{
			new = lex_new(splited[j], check_separator(splited[j]));
			lex_add_back(list, new, 0);
			j++;
		}
	}
}

/* Count how many node are needed to separate the content and create the new nodes
@param content -> the content to check
@return the number of node needed
*/
int	manage_separator(char *content, t_lexer **list)
{
	char	**splited;
	int		count;
	int		i;

	if (!content)
		return (0);
	count = 1;
	i = -1;
	splited = ft_split(content, ' ');
	if (!splited)
		return (0);
	while (splited[++i])
	{
		if (check_separator(splited[i]))
			count++;
		if (i > 0)
			if (!check_separator(splited[i]) && check_separator(splited[i - 1]))
				count++;
	}
	create_separators_nodes(splited, count, list);
	return (count);
}

/* Call all functions for separate the list
@param list -> the list to iterate
@return new list separated
*/
t_lexer	*handle_separator(t_lexer **list)
{
	t_lexer	*tmp;
	t_lexer	*new;

	tmp = *list;
	new = NULL;
	while (tmp)
	{
		if (tmp->type == UNDEF)
			manage_separator(tmp->content, &new);
		else
			lex_add_back(&new, lex_new(tmp->content, tmp->type), 0);
		tmp = tmp->next;
	}
	return (new);
}
