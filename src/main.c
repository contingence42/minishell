/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:20:21 by kdaumont          #+#    #+#             */
/*   Updated: 2024/01/31 09:48:14 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>

void	show_prompt()
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
		add_history(inpt);
		printf("%s", inpt);
		printf("\n");
		++i;
	}
}

int	main()
{
	show_prompt();
	return (0);
}
