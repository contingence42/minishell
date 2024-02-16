/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/02/16 10:16:12 by aattali          ###   ########.fr       */
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

	pos = ft_strchrpos(content, '=');
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
 * @brief sort the given env-list in place
 *
 * @param env the environment in linked-list
 */
static void	bubble_sort(t_env **env)
{
	t_env	*temp;
	char	*temp2;
	bool	sorted;

	sorted = false;
	while (!sorted)
	{
		sorted = true;
		temp = *env;
		while (temp->next)
		{
			if (ft_strcmp(temp->key, temp->next->key) > 0)
			{
				sorted = false;
				temp2 = temp->key;
				temp->key = temp->next->key;
				temp->next->key = temp2;
				temp2 = temp->value;
				temp->value = temp->next->value;
				temp->next->value = temp2;
			}
			temp = temp->next;
		}
	}
}

/**
 * @brief duplicate the given env to dest
 *
 * @param src the original env to be copied
 * @param dst the destination env
 */
static void	env_dup(t_env *src, t_env **dst)
{
	t_env	*node;

	while (src)
	{
		node = ft_calloc(1, sizeof(*node));
		node->before = NULL;
		node->next = NULL;
		node->key = ft_strdup(src->key);
		node->value = ft_strdup(src->value);
		env_add_back(dst, node);
		src = src->next;
	}
}

/**
 * @brief print the env list in the correct format for export
 *
 * @param env the environment in linked-list
 */
static void	print_env(t_env *env)
{
	while (env)
	{
		printf("export %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

/**
 * @brief print the environment without args, or add/modify a variable
 *
 * @param executor the struct of the exec process
 * @param command the linked-list of commands
 */
void	ft_export(t_executor *executor, t_commands *command)
{
	size_t	i;
	t_env	*senv;

	if (!command->cmd[1])
	{
		senv = NULL;
		env_dup(*(executor->env), &senv);
		if (!senv)
			return ;
		bubble_sort(&senv);
		print_env(senv);
		env_clear(&senv);
	}
	else
	{
		i = 0;
		while (command->cmd[++i])
			add_or_replace(executor->env, command->cmd[i]);
	}
}
