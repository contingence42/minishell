/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/02/15 11:12:40 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**recreate_env(t_executor *executor, int pos, int len)
{
	int		i;
	int		j;
	char	**new_env;

	if (len == 1)
	{
		new_env = ft_calloc(1, sizeof(char *));
		if (!new_env)
			return (NULL);
	}
	else
	{
		new_env = ft_calloc(len, sizeof(char *));
		if (!new_env)
			return (NULL);
		i = -1;
		j = 0;
		while (++i < len)
		{
			if (i == pos)
				j++;
			new_env[i] = ft_strdup(*(executor->env)[j++]);
		}
	}
	return (new_env);
}

void	ft_unset(t_executor *executor, t_commands *command)
{
	int		i;
	int		pos;
	int		len;
	char	**new_env;

	i = 0;
	while (command->cmd[++i])
	{
		pos = get_env_pos(*(executor->env), command->cmd[i]);
		if (pos == -1)
			continue ;
		len = ft_stralen(*(executor->env));
		new_env = recreate_env(executor, pos, len);
		ft_free_astr(*(executor->env));
		*(executor->env) = new_env;
	}
}
