/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:34:14 by alexfuen          #+#    #+#             */
/*   Updated: 2026/03/08 13:34:16 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

t_token	*lexer(char *str);
int		parser(t_token *lexer);
void	check_quote(char *str);
void	free_split(char **split);
int		split_len(char **split);

#endif
