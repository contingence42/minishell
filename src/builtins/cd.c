/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:03:14 by kdaumont          #+#    #+#             */
/*   Updated: 2024/02/06 13:44:15 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Change the working directory by wanted path, like cd
@param cmd -> t_command struct pointer
@return :
	- 0 : fail execution
	- 1 : success execution
*/
int	ft_cd(t_command *cmd)
{
	if (ft_strcmp(cmd->cmd_name, "cd") != 0 || !cmd->builtin)
		return (EXIT_FAILURE);
	if (ft_stralen(cmd->cmd) == 1)
	{
		if (chdir(getenv("HOME")) == -1)
			return (0);
	}
	else if (ft_stralen(cmd->cmd) == 2)
	{
		if (chdir(cmd->cmd[1]) == -1)
			return (0);
	}
	else
		return (0);
	return (1);
}
