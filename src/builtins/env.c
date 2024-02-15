/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/02/15 09:57:25 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief print the environment
 *
 * @param executor the struct of the exec process
 */
void	ft_env(t_executor *executor)
{
	char	**env;
	size_t	i;

	env = *(executor->env);
	i = -1;
	while (env && env[++i])
		printf("%s\n", env[i]);
}
