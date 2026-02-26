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

static void	handler(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	write(1, ">", 1);
}

int	main(int argc, char **argv)
{
	char *str;

	signal(SIGINT, handler);
	exec(argc, argv);

	return (0);
}
