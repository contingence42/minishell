/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:49:33 by aattali           #+#    #+#             */
/*   Updated: 2024/02/19 10:42:20 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief update the linked-list to create the needed nodes
 *
 * @param node the node to be separated, where a variable to be expanded exist
 * @param pos_d the position of the $ character
 * @param pos_e the position of ' ', signifying the end of the variable
 */
static void	update_lex(t_lexer *node, int pos_d, int pos_e)
{
	int		len;
	char	*content;

	content = node->content;
	len = ft_strlen(content);
	if (pos_e == -1)
		lex_add_after(&node, lex_new(ft_substr(content, pos_d + 1, len),
				DOLLAR));
	else
	{
		lex_add_after(&node, lex_new(ft_substr(content, pos_d + 1, pos_e),
				DOLLAR));
		lex_add_after(&(node->next), lex_new(ft_substr(content, pos_e, len),
				node->type));
	}
	node->content = ft_substr(content, 0, pos_d);
	free(content);
}

/**
 * @brief create new DOLLAR nodes between existing nodes if expansion is needed
 *
 * @param list the linked-list of the lexer
 */
static void	separate_dollars(t_lexer *list)
{
	int		pos_d;
	int		pos_e;

	while (list)
	{
		if (list->type != SQUOTE && list->type != DOLLAR)
		{
			pos_d = ft_strchrpos(list->content, '$');
			if (pos_d == -1)
			{
				list = list->next;
				continue ;
			}
			pos_e = ft_strchrpos(list->content + pos_d, ' ');
			update_lex(list, pos_d, pos_e);
		}
		list = list->next;
	}
}

/**
 * @brief expand the variable using the environment
 *
 * if the variable doesn't exist inside the environment, the result is NULL
 *
 * @param list the linked-list of the lexer
 * @param env the linked-list of the environment
 */
static void	expand(t_lexer *list, t_env *env)
{
	t_env	*envr;

	while (list)
	{
		if (list->type == DOLLAR)
		{
			envr = env_get(env, list->content);
			if (envr)
			{
				free(list->content);
				list->content = ft_strdup(envr->value);
			}
			else
			{
				free(list->content);
				list->content = NULL;
			}
		}
		list = list->next;
	}
}

/**
 * @brief expand the variables inside the linked-list
 *
 * TODO:error handling
 * NOTE:the expanded variable in bash will not be interpreted by the parser
 * we can consider the variable to be between double quotes
 *
 * @param list the linked-list of the lexer
 * @param minishell the general struct of the program
 */
void	handle_expansion(t_lexer **list, t_minishell *minishell)
{
	t_env	*env;

	env = minishell->env;
	separate_dollars(*list);
	expand(*list, env);
}
