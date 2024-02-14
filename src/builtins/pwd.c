/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/02/12 15:19:24 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print the current working directory, like pwd
 */
void	ft_pwd(void)
{
	int		size;
	char	*buffer;

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
