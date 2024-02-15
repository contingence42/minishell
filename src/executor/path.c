/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:21:26 by aattali           #+#    #+#             */
/*   Updated: 2024/02/15 09:26:19 by aattali          ###   ########.fr       */
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
