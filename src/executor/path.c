/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:21:26 by aattali           #+#    #+#             */
/*   Updated: 2024/02/15 10:34:24 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief find and allocate the variable path from the env
 *
 * @param executor the struct of the exec process
 */
void	find_path(t_executor *executor)
{
	size_t	i;
	char	**env;

	if (executor->path)
		ft_free_astr(executor->path);
	i = -1;
	executor->path = NULL;
	env = *(executor->env);
	while (env && env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			executor->path = ft_split((env[i]) + 5, ':');
			break ;
		}
	}
}

/**
 * @brief get the position i of a variable in the environment
 *
 * @param env the environment
 * @param key the variable to find
 * @return the position of the variable, or -1 if not found
 */
int	get_env_pos(char **env, char *key)
{
	size_t	i;

	i = -1;
	while (env && env[++i])
	{
		if (!ft_strncmp(env[i], key, ft_getinset('=', key)))
			return (i);
	}
	return (-1);
}
