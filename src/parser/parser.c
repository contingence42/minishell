/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:37:43 by aattali           #+#    #+#             */
/*   Updated: 2024/02/20 09:35:18 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * @brief check if the node is a io associated type
 *
 * @param type the type of the node
 * @return boolean
 */
static bool	is_io(t_lextype type)
{
	return (type == HEREDOC || type == RDR_IN || type == RDR_OUT_T
		|| type == RDR_OUT_A || type == INFILE || type == OUTFILE);
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
 * @brief parse the given node and call the necessary functions
 *
 * TODO: error handling
 *
 * @param node the node of a lexed element
 * @param executor the struct of the exec process
 * @param command the linked-list of commands
 */
static void	dispatch(t_lexer *node, t_executor **executor, t_commands **command)
{
	char	**tmp;
	int		len;
	int		i;

	tmp = NULL;
	i = 0;
	if (!tmp)
	{
		len = cmdlen(node);
		tmp = ft_calloc(len, sizeof(*tmp));
	}
	if (node->type == PIPE)
	{
		(*executor)->ispipe = true;
		cmd_add_back(command, cmd_new(tmp));
		tmp = NULL;
		i = 0;
	}
	else if (is_cmd(node->type) && node->content)
		tmp[i++] = ft_strdup(node->content);
	else if (is_io(node->type))
		io_handler(node, executor, command);
}

/**
 * @brief parse every lexed elements et populate executor and command
 *
 * TODO:error handling
 *
 * @param lex the linked-list of lexed elements
 * @param executor the struct of the exec process
 * @param command the linked-list of commands
 */
void	parser(t_lexer *lex, t_executor **executor, t_commands **command)
{
	*executor = ft_calloc(1, sizeof(**executor));
	*command = NULL;
	while (lex)
	{
		dispatch(lex, executor, command);
		lex = lex->next;
	}
}
