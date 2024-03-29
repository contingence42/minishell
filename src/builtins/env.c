/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/02/15 13:58:37 by aattali          ###   ########.fr       */
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
	t_env	*env;

	env = *(executor->env);
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
