/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>          +#+  +:+       +#+          */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:03:14 by aattali          #+#    #+#              */
/*   Updated: 2024/02/26 11:01:27 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Change the working directory by wanted path, like cd
@param cmd -> t_commands struct pointer
*/
void	ft_cd(t_commands *cmd)
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
