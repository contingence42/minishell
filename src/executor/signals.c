/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmetehri <bmetehri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:13:54 by bmetehri          #+#    #+#             */
/*   Updated: 2024/03/18 14:07:53 by bmetehri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_code = SIGINT;
	}
	if (sig == SIGQUIT)
		g_signal_code = SIGQUIT;
}

void	signal_initializer(int signal_received, bool its_heredoc)
{
	if (its_heredoc && signal_received == SIGINT)
		signal(SIGINT, heredoc_signal_handler);
	else
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
	}
}

void	heredoc_signal_handler(int sig)
{
	(void) sig;
}
