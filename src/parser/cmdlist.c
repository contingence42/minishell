/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:39:24 by aattali           #+#    #+#             */
/*   Updated: 2024/02/20 10:21:54 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief give the last node of the linked-list
 *
 * @param command the linked-list of commands
 * @return the last node
 */
static t_commands	*cmd_last(t_commands *command)
{
	if (command)
		while (command->next)
			command = command->next;
	return (command);
}

/**
 * @brief check if the command is a builtin
 *
 * @param cmd the name of the command
 * @return boolean
 */
static bool	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit"))
		return (true);
	else if (!ft_strcmp(cmd, "unset"))
		return (true);
	else if (!ft_strcmp(cmd, "cd"))
		return (true);
	else if (!ft_strcmp(cmd, "env"))
		return (true);
	else if (!ft_strcmp(cmd, "export"))
		return (true);
	else if (!ft_strcmp(cmd, "pwd"))
		return (true);
	else if (!ft_strcmp(cmd, "unset"))
		return (true);
	return (false);
}

/**
 * @brief create a new node in the linked-list of commands
 *
 * @param content the cmd splitted in a array of strings
 * @return the node created or NULL if error
 */
t_commands	*cmd_new(char	**content)
{
	t_commands	*node;

	if (!content)
		return (NULL);
	node = ft_calloc(1, sizeof(*node));
	if (!node)
		return (NULL);
	node->cmd = content;
	node->cmd_name = content[0];
	node->builtin = false;
	if (is_builtin(node->cmd_name))
		node->builtin = true;
	node->first = false;
	node->last = false;
	node->next = NULL;
	return (node);
}

/**
 * @brief add a new node at the end of the linked-list
 *
 * @param command the linked-list of commands
 * @param node the new node to be added
 */
int	cmd_add_back(t_commands **command, t_commands *node)
{
	t_commands	*last;

	if (!node)
		return (malloc_error());
	if (!*command)
	{
		node->first = true;
		*command = node;
		return (EXIT_SUCCESS);
	}
	last = cmd_last(*command);
	node->next = last->next;
	last->last = false;
	node->last = true;
	last->next = node;
	return (EXIT_SUCCESS);
}
