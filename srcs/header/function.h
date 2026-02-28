#ifndef FUNCTION_H
# define FUNCTION_H

char	***lexer(char *str, char **envp);
void	print_header(void);
int		exists(char *str, char **envp);
int		ft_memlen(char **split);

#endif
