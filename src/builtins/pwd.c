/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/02/14 13:15:13 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print the current working directory, like pwd
 */
void	ft_pwd(t_commands *command)
{
	int		size;
	char	*buffer;

	(void)command;
	size = 1;
	buffer = NULL;
	while (getcwd(buffer, size) == NULL)
		size++;
	buffer = malloc(sizeof(char) * (size - 1));
	if (!buffer)
		return ;
	if (getcwd(buffer, size))
		printf("%s\n", getcwd(buffer, size));
	free(buffer);
}
