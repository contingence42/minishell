/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:03:14 by kdaumont          #+#    #+#             */
/*   Updated: 2024/02/06 13:50:10 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Change the working directory by wanted path, like cd
@param cmd -> t_command struct pointer
*/
void	ft_cd(t_command *cmd)
{
	if (ft_stralen(cmd->cmd) == 1)
	{
		if (chdir(getenv("HOME")) == -1)
			return ;
	}
	else if (ft_stralen(cmd->cmd) == 2)
	{
		if (chdir(cmd->cmd[1]) == -1)
			return ;
	}
}
