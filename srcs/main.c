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

static void	handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;

	if (sig == SIGINT)
		write(1, "\n> ", 3);
	else if (sig == SIGQUIT)
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

int	main(int argc, char **argv, char **envp)
{
	struct sigaction sa;
	char *str;
	
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
	
	write(1, "============================= WELCOME TO MINISHELL =============================", 80);
	write(1, "\n> ", 3);
	while (1)
	{
		str = get_next_line(0);
		if (str && *str)
			str[ft_strlen(str) - 1] = '\0';
		if (!str)
			exit(0);
		exec(str, envp);
		free(str);
		write(1, "> ", 2);
	}
	return (0);
}
