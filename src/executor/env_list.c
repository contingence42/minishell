/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:52:51 by aattali           #+#    #+#             */
/*   Updated: 2024/02/15 15:59:55 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief create a new node in the linked-list
 *
 * @param content a key-value pair separated with '='
 * @return the node created
 */
t_env	*env_new(char *content)
{
	t_env	*node;
	int		pos;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	pos = ft_getinset('=', content);
	if (pos == -1)
		return (NULL);
	node->key = ft_substr(content, 0, pos);
	node->value = ft_substr(content, pos + 1, ft_strlen(content + pos));
	node->next = NULL;
	node->before = NULL;
	return (node);
}

/**
 * @brief get the last node of the linked-list
 *
 * @param list the linked-list of the environment
 * @return the last node
 */
t_env	*env_last(t_env *list)
{
	if (list)
		while (list->next)
			list = list->next;
	return (list);
}

/**
 * @brief the node in the linked-list identified by the key given
 *
 * @param list the linked-list of the environment
 * @param key the key to be found for the variavble
 * @return the node or NULL if not found
 */
t_env	*env_get(t_env *list, char *key)
{
	while (list)
	{
		if (!strcmp(key, list->key))
			return (list);
		list = list->next;
	}
	return (NULL);
}

/**
 * @brief add the node as the last elem in the linked-list
 *
 * @param list the linked-list of the environment
 * @param node a node created by env_new
 */
void	env_add_back(t_env **list, t_env *node)
{
	t_env	*last;

	if (!node)
		return ;
	if (!*list)
	{
		*list = node;
		return ;
	}
	last = env_last(*list);
	node->next = last->next;
	node->before = last;
	last->next = node;
}

/**
 * @brief free the strings inside every node, then the node itself
 *
 * @param list the linked-list of the environment
 */
void	env_clear(t_env **list)
{
	t_env	*next;

	if (!list)
		return ;
	while (*list)
	{
		next = (*list)->next;
		free((*list)->key);
		free((*list)->value);
		free(*list);
		*list = next;
	}
	*list = NULL;
}
