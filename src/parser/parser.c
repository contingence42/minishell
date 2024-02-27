/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:37:43 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:46:02 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/**
 * @brief check if the node is a cmd associated type
 *
 * @param type the type of the node
 * @return boolean
 */
static bool	is_cmd(t_lextype type)
{
	return (type == COMMAND || type == DQUOTE || type == SQUOTE
		|| type == DOLLAR);
}

/**
 * @brief give the length of a command, to be malloc'd
 *
 * @param lex the linked list of lexed elements
 * @return the length
 */
static int	cmdlen(t_lexer *lex)
{
	int	i;

	i = 0;
	while (lex)
	{
		if (lex->type == PIPE)
			break ;
		if (is_cmd(lex->type) && lex->content)
			i++;
		lex = lex->next;
	}
	return (i);
}

/**
 * @brief accumulate the splitted cmd array
 *
 * @param node the node of a lexed element
 * @param tmp the cmd splitted into an array of strings
 * @param i incrementer given as pointer thanks to the norm
 * @return error code in case of malloc errors
 */
static int	accumulate_cmd(t_lexer *node, char **tmp, int *i)
{
	if (!is_cmd(node->type) || !node->content)
		return (EXIT_SUCCESS);
	tmp[*i] = ft_strdup(node->content);
	if (!tmp[*i])
		return (ft_free_astr(tmp), malloc_error());
	(*i)++;
	return (EXIT_SUCCESS);
}

/**
 * @brief parse the given node and call the necessary functions
 *
 * @param node the node of a lexed element
 * @param exec the struct of the exec process
 * @param cmd the linked-list of commands
 * @param i incrementer given as pointer thanks to the norm
 * @return error code in case of malloc errors
 */
static int	dispatch(t_lexer *node, t_executor *exec, t_commands **cmd, int *i)
{
	char	**tmp;
	int		len;

	tmp = NULL;
	while (node)
	{
		if (!tmp)
		{
			len = cmdlen(node);
			tmp = ft_calloc(len + 1, sizeof(*tmp));
			if (!tmp)
				return (malloc_error());
		}
		if (io_handler(&node, exec, cmd) == EXIT_FAILURE)
			return (ft_free_astr(tmp), EXIT_FAILURE);
		if (node->type == PIPE && pipe_handler(exec, cmd, &tmp, i))
			return (EXIT_FAILURE);
		else if (accumulate_cmd(node, tmp, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		node = node->next;
	}
	if (push_cmd(cmd, &tmp, i) == EXIT_FAILURE)
		return (ft_free_astr(tmp), malloc_error());
	return (EXIT_SUCCESS);
}

/**
 * @brief parse every lexed elements et populate executor and command
 *
 * @param lex the linked-list of lexed elements
 * @param executor the struct of the exec process
 * @param command the linked-list of commands
 * @return error code in case of malloc errors
 */
int	parser(t_lexer *lex, t_executor **executor, t_commands **command)
{
	int	i;

	i = 0;
	*executor = ft_calloc(1, sizeof(**executor));
	if (!*executor)
		return (malloc_error());
	*command = NULL;
	if (dispatch(lex, *executor, command, &i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
