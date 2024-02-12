/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/02/12 16:30:47 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Exit the program with the nice error code, like exit
@param commands -> t_commands struct pointer
*/
void	ft_exit(t_command *commands)
{
	int		code;
	int		len;
	char	*str;

	len = ft_stralen(commands->cmd);
	code = 0;
	if (len > 2)
		return ((void)ft_dprintf(2, "exit: too many arguments\n"));
	if (len == 1)
		code = 0;
	else if (len == 2)
	{
		code = ft_atoi(commands->cmd[1]);
		str = ft_itoa(code);
		if (!str)
			return ;
		if (ft_strcmp(commands->cmd[1], str) != 0)
			(ft_dprintf(2, "exit: %s: numeric argument required\n",
					commands->cmd[1]), code = 2);
		free(str);
	}
	exit(code);
}
