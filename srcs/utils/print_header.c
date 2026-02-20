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
	printf("\n");
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
}
