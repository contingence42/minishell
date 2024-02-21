/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:49:33 by aattali           #+#    #+#             */
/*   Updated: 2024/02/21 11:22:21 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief update the linked-list to create the needed nodes
 *
 * @param node the node to be separated, where a variable to be expanded exist
 * @param pos_d the position of the $ character
 * @param pos_e the position of ' ', signifying the end of the variable
 * @param err the error code that will be toggled if there's a malloc error
 */
static void	update_lex(t_lexer *node, int pos_d, int pos_e, int *err)
{
	int		len;
	char	*content;

	content = node->content;
	len = ft_strlen(content);
	if (pos_e == -1)
		lex_add_after(&node, lex_new(ft_substr(content, pos_d + 1, len),
				DOLLAR), err);
	else
	{
		lex_add_after(&node, lex_new(ft_substr(content, pos_d + 1, pos_e),
				DOLLAR), err);
		lex_add_after(&(node->next), lex_new(ft_substr(content, pos_e, len),
				node->type), err);
	}
	node->content = ft_substr(content, 0, pos_d);
	if (!node->content)
		*err = 1;
	free(content);
}

/**
 * @brief create new DOLLAR nodes between existing nodes if expansion is needed
 *
 * @param list the linked-list of the lexer
 * @return error code in case of malloc errors
 */
static int	separate_dollars(t_lexer *list)
{
	int		pos_d;
	int		pos_e;
	int		err;

	err = 0;
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
			update_lex(list, pos_d, pos_e, &err);
		}
		list = list->next;
	}
	return (err);
}

/**
 * @brief expand the variable using the environment
 *
 * if the variable doesn't exist inside the environment, the result is NULL
 *
 * @param list the linked-list of the lexer
 * @param env the linked-list of the environment
 * @return error code in case of malloc errors
 */
static int	expand(t_lexer *list, t_env *env)
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
				if (!list->content)
					return (EXIT_FAILURE);
			}
			else
			{
				free(list->content);
				list->content = NULL;
			}
		}
		list = list->next;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief expand the variables inside the linked-list
 *
 * NOTE:the expanded variable in bash will not be interpreted by the parser
 * we can consider the variable to be between double quotes
 *
 * @param list the linked-list of the lexer
 * @param minishell the general struct of the program
 * @return error code in case of malloc errors
 */
int	handle_expansion(t_lexer **list, t_minishell *minishell)
{
	t_env	*env;
	int		err;

	env = minishell->env;
	err = separate_dollars(*list);
	if (!err)
		err = expand(*list, env);
	if (err)
		return (malloc_error());
	return (EXIT_SUCCESS);
}
