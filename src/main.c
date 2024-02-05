/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:20:21 by kdaumont          #+#    #+#             */
/*   Updated: 2024/02/06 14:01:11 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_prompt(void)
{
	char	*inpt;
	int		i;

	i = 0;
	while (true)
	{
		inpt = readline("minishell$ ");
		if (ft_strcmp(inpt, "exit") == 0)
			break ;
		if (ft_strcmp(inpt, "history -c") == 0)
			rl_clear_history();
		if (ft_strlen(inpt) > 0)
			add_history(inpt);
		printf("\n");
		++i;
	}
}

int	main(void)
{
	show_prompt();
	return (0);
}
