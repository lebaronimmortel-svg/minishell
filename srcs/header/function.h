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
void	exec_main(char **envp, char **split);
void	execve_error(char *str, char *command);
void	free_split_exec(t_exec *exec);
void	main_loop(char **split, t_token *lex, char **envp);
void	print_lexer(t_token *lexer);
void	print_icon(int flag);
void	loop(t_token *lexer, char **split);

#endif
