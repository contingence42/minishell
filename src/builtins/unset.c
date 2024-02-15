/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/02/15 14:51:24 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief remove variables inside the environment
 *
 * @param executor the struct of the exec process
 * @param command the linked-list of commands
 */
void	ft_unset(t_executor *executor, t_commands *command)
{
	int		i;
	t_env	*node;

	i = 0;
	while (command->cmd[++i])
	{
		node = env_get(*(executor->env), command->cmd[i]);
		if (!node)
			continue ;
		free(node->value);
		free(node->key);
		node->before->next = node->next;
		node->next->before = node->before;
		free(node);
	}
}
