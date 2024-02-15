/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/02/15 14:53:06 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief add a variable to the environment, or update it
 *
 * @param env the environment in linked-list
 * @param content a variable to be added to the env
 */
void	add_or_replace(t_env **env, char *content)
{
	t_env	*node;
	char	*key;
	int		pos;

	pos = ft_getinset('=', content);
	if (pos == -1)
		return ;
	key = ft_substr(content, 0, pos);
	node = env_get(*env, key);
	if (!node)
		env_add_back(env, env_new(content));
	else
		node->value = ft_substr(content, pos, ft_strlen(content + pos));
	free(key);
}

/**
 * @brief print the environment without args, or add/modify a variable
 *
 * TODO: handle export without args, sort the linked-list
 *
 * @param executor the struct of the exec process
 * @param command the linked-list of commands
 */
void	ft_export(t_executor *executor, t_commands *command)
{
	size_t	i;

	if (!command->cmd[1])
	{
		printf("todo");
	}
	else
	{
		i = 0;
		while (command->cmd[++i])
			add_or_replace(executor->env, command->cmd[i]);
	}
}
