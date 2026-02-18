#include "../header/header.h"

void	print_first_line(void)
{
	int k;
	
	k = 0;
	while (k < 2)
	{
		write (1,"	",1);
		k++;
	}
	write(1, "MINISHELL", 9);
	while (k < 7)
	{
		write (1,"	",1);
		k++;
	}
	write(1, "alexfuen", 8);
}

void	print_second_line(void)
{
	int k;
	
	k = 0;
	while (k < 8)
	{
		write (1,"	",1);
		k++;
	}
	write(1, "lukrodri", 8);
}

void print_header(void)
{
	int i;
	int j;

	i = 0;
	j = 0;
	write(1, "\n", 1);
	write(1, "\n", 1);
	while (j < 3)
	{
		i = 0;
		while (i < 72)
		{
			write(1, "█", 3);
			i++;
		}
		write(1, "\n", 1);
		if (j == 0)
			print_first_line();
		if (j == 1)
			print_second_line();
		write(1, "\n", 1);
		j++;
	}
}
