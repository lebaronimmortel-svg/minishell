#ifndef FUNCTION_H
# define FUNCTION_H

char	**lexer(char *str);
void	print_header(void);
void	lex_convert(char **split, char **envp);
int		exists(char *str, char **envp);

#endif
