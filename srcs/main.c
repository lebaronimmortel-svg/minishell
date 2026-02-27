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

static void	handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;

	if (sig == SIGINT)
		write(1, "\n> ", 3);
	else if (sig == SIGQUIT)
		return ;
}

void disable_echoctl(void)
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction sa;
	char *str;
	char **split;
	
	(void) argc;
	(void) argv;
	
	disable_echoctl();
	
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	print_header();
	write(1, "\n> ", 3);
	while (1)
	{
		str = get_next_line(0);
		if (str && *str)
			str[ft_strlen(str) - 1] = '\0';
		if (!str)
			exit(0);
		split = lexer(str);
		lex_convert(split, envp);
		free(str);
		free_split(split);
		write(1, "> ", 2);
	}
	return (0);
}
