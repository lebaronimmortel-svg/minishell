/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 06:44:34 by lukrodri          #+#    #+#             */
/*   Updated: 2026/02/17 06:44:36 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/header.h"
/*
static void free_split(char **split)
{
	unsigned int i;
	
	if (!split || !(*split))
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
*/

char **my_realloc(char **mem)
{
	char **tmp;
	int len;
	int i;
	
	if (!mem)
		return (NULL);
	len = ft_memlen(mem);
	tmp = mem;
	mem = malloc(len + 2 * sizeof(char *));
	if (!mem)
		return (NULL);
	i = 0;
	while (i < len)
	{	
		mem[i] = tmp[i];
		free(tmp[i]);
		i++;
	}
	return (mem);
}

static void	handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;

	if (sig == SIGINT)
		write(1, "\n> ", 3);
	else if (sig == SIGQUIT)
		return ;
}

static void	print_lexer(char ***lexer)
{
	int	i;

	i = 0;
	write(1, "\n ", 2);
	while (lexer[0][i])
	{

		write(1, lexer[1][i], ft_strlen(lexer[1][i]));
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	return ;
}

// ca c'est ce qui fait que Ctrl-\ ne fait rien (merci ChatGPT)
void disable_echoctl(void)
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char *iso_quote(char **str)
{
	int i;
	int j;
	int len;
	char c;
	char *iso;
	
	i = 0;
	iso = NULL;
	while ((*str)[i])
	{
		if (((*str)[i] == 39 && (*str)[i + 1]) || ((*str)[i] == 34 && *(str)[i + 1]))
		{
			*str += 1;
			iso = iso_quote(str);
			*str -= 1;
			if (iso)
				return (iso);
			c = (*str)[i];
			i++;
			while((*str)[i] != c)
			{
				if ((*str)[i] == '\0')
					return (NULL);
				i++;
			}
			len = i;
			iso = malloc(len + 1);
			if (!iso)
				return (NULL);
			iso[len] = '\0';
			i = 0;
			while ((*str)[i] != c)
				i++;
			j = 1;
			iso[0] = (*str)[i];
			while ((*str)[i + j] != c)
			{
				iso[j] = (*str)[i + j];
				j++; 
			}
			iso[j] = (*str)[i + j];
			(*str)[i] = '#';
			ft_memmove(&((*str)[i + 1]), &((*str)[i + j + 1]), j);
			break;
		}
		else
			i++;
	}
	return (iso);
}

char **do_quote(char **str)
{
	int i;
	char **quote_arr;
	char *next_quote;
	char **tmp;
	
	quote_arr = malloc(sizeof(char *) * 2);
	if (!quote_arr)
		return (NULL);
	i = 0;
	next_quote = iso_quote(str);
	while (next_quote)
	{
		quote_arr[i] = next_quote;
		quote_arr[i + 1] = NULL;
		tmp = my_realloc(quote_arr);
		if (!tmp)
			return (NULL);
		quote_arr = tmp;
		next_quote = iso_quote(str);
		i++;
		
	}
	return (quote_arr);
}

void	print_parser(char ***lexer)
{
	int i;
	
	
	write (1, "===============================\n\n", 33); 
	i = 0;
	while (lexer[1][i])
	{
		if (!ft_strncmp(lexer[1][i], "PIP", 3))
		{
			write(1, "\n    ||\n", 8);
			write(1, " PIPE WITH\n", 11);
			write(1, "    ||\n", 7);
		}
		else
		{
			if (!ft_strncmp(lexer[0][i], "Unknown :", 9))
				write(1, &lexer[0][i][9], ft_strlen(lexer[0][i]) - 9);
			else
				write(1, lexer[0][i], ft_strlen(lexer[0][i]));
			write(1, " ", 1);	
		}
		i++;
	}
	write(1, "\n\n", 2);
	write (1, "===============================\n\n", 33); 
}

/*
void	split_lexer(char ***lex)
{
	char **split;
	char *join;
	int i;
	
	i = 0;
	while (lex[0][i])
		join = ft_strjoin(join, (lex[0][i++]));
	split = ft_split(join, '|');
	i = 0;
	while (split[i])
	{
		split[i] = ft_strtrim(split[i], " ");
		if (!ft_strncmp(split[i], "Unknown : ", 10))
		{
			split[i] = ft_memmove(split[i], &split[i][10], ft_strlen(split[i]) - 10);
			split[i][ft_strlen(split[i]) - 10] = '\0';	
		}
		else if (!ft_strncmp(split[i], "UNKUnknown : ", 13))
		{
			split[i] = ft_memmove(split[i], &split[i][13], ft_strlen(split[i]) - 13);
			split[i][ft_strlen(split[i]) - 13] = '\0';	
		}
		i++;
	}
	print_split(split);
	//free_split(split);
}
*/

//ignorer les quotes !
int	main(int argc, char **argv, char **envp)
{
	struct sigaction sa;
	char *str;
	char ***lex;
	//char **quote;
	
	(void) argc;
	(void) argv;
	
	// desactiver la touche Ctrl-\ .
	disable_echoctl();
	
	// intercepter les touches Ctrl-C et Ctrl-D
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	//
	print_header();
	write(1, "\n> ", 3);
	while (1)
	{
		str = get_next_line(0);
		if (str && *str)
			str[ft_strlen(str) - 1] = '\0';
		if (!str)
			exit(0);
		//quote = do_quote(&str);
		lex = lexer(str, envp);
		print_lexer(lex);
		print_parser(lex);
		write(1, "\n", 1);
		free(str);
		//free_split(split);
		write(1, "> ", 2);
	}
	return (0);
}
