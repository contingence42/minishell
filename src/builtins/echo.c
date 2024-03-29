/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>          +#+  +:+       +#+          */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:28:17 by aattali          #+#    #+#              */
/*   Updated: 2024/02/26 11:01:34 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print the parameters, like 'echo' command
@param cmd -> t_commands struct pointer
*/
void	ft_echo(t_commands *cmd)
{
	size_t	len;
	size_t	i;

	len = ft_stralen(cmd->cmd);
	if (len > 1 && ft_strncmp(cmd->cmd[1], "-", 1) != 0)
		i = 1;
	else
		i = 2;
	if (len == 1)
		return ((void)printf("\n"));
	if (len == 2 && ft_strncmp(cmd->cmd[1], "-", 1) == 0)
		return ;
	while (cmd->cmd[i])
	{
		printf("%s", cmd->cmd[i]);
		if (i != len - 1)
			printf(" ");
		i++;
	}
	if (ft_strncmp(cmd->cmd[1], "-", 1) != 0)
		printf("\n");
}
