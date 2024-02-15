/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:21:26 by aattali           #+#    #+#             */
/*   Updated: 2024/02/15 14:11:48 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief get the size of the linked-list env
 *
 * @param list the environment in linked-list
 * @return size
 */
static size_t	env_size(t_env *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

/**
 * @brief find and allocate the variable path from the env
 *
 * @param executor the struct of the exec process
 */
void	find_path(t_executor *executor)
{
	t_env	*envpath;

	if (executor->path)
		ft_free_astr(executor->path);
	executor->path = NULL;
	envpath = env_get(*(executor->env), "PATH");
	executor->path = ft_split(envpath->value, ':');
}

/**
 * @brief transform the linked-list of env into a array of strings
 *
 * @param list the environent in linked-list
 * @return the environment in array of strings
 */
char	**env_collapse(t_env *list)
{
	char	**env;
	size_t	i;

	env = ft_calloc(env_size(list) + 1, sizeof(*env));
	if (!env)
		return (NULL);
	i = 0;
	while (list)
	{
		env[i] = ft_strjoin3(list->key, "=", list->value);
		list = list->next;
		i++;
	}
	return (env);
}
