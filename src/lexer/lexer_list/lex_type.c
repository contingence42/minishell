/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:44:17 by aattali           #+#    #+#             */
/*   Updated: 2024/02/26 10:44:20 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lextype	get_lextype(char c, int dbl)
{
	if (c == '<' && dbl)
		return (HEREDOC);
	if (c == '<')
		return (RDR_IN);
	if (c == '>' && dbl)
		return (RDR_OUT_A);
	if (c == '>')
		return (RDR_OUT_T);
	if (c == '|')
		return (PIPE);
	return (UNDEF);
}
