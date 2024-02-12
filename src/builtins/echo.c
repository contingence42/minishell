/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:28:17 by kdaumont          #+#    #+#             */
/*   Updated: 2024/02/12 13:22:39 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print the parameters, like 'echo' command
@param cmd -> t_command struct pointer
*/
void	ft_echo(t_command *cmd)
{
	size_t	len;
	int		i;

	len = ft_stralen(cmd->cmd);
	if (len > 1 && ft_strncmp(cmd->cmd[1], "-", 1) != 0)
		i = 1;
	else
		i = 2;
	if (len == 1)
		return (printf("\n"), 1);
	if (len == 2 && ft_strncmp(cmd->cmd[1], "-", 1) == 0)
		return (0);
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
