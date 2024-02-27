/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:39:03 by aattali           #+#    #+#             */
/*   Updated: 2024/02/27 10:40:03 by aattali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

bool		lex_malloc_check(t_lexer *list);
void		lex_clear(t_lexer **list);
void		lex_trim(t_lexer **list, int *err);
void		lex_add_back(t_lexer **list, t_lexer *node, int *err);
void		lex_add_before(t_lexer *list, t_lexer *node);
void		lex_add_after(t_lexer **list, t_lexer *node, int *err);
t_lexer		*lex_new(char *content, t_lextype type);
t_lexer		*lex_geti(t_lexer *list, size_t index);
t_lexer		*lex_last(t_lexer *list);
t_lextype	get_lextype(char c, int dbl);

t_lexer		*lexer(char *line, t_minishell *minishell);
t_lexer		*handle_quotes(char *line);
int			handle_expansion(t_lexer **list, t_minishell *minishell);
int			handle_separators(t_lexer **list);
int			handle_cmdio(t_lexer **list);

#endif
