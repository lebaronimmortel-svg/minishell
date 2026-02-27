#include "../header/header.h"

void	print_lexer(char **split)
{
	int i;
	
	i = 0;
	write(1, "LEXER : ", 8);
	if (*split)
	{
		while (split[i])
		{
			write(1, split[i], ft_strlen(split[i]));
			if (split[i + 1])
				write(1, " / ", 3);
			i++;
		}
	}
	write(1, "\n", 1);
}

char **lexer(char *str)
{
	char **split;

	split = ft_split(str, ' ');
	return (split);
}

void	lex_convert(char **split, char **envp)
{
	int i;
	char unk[7] = "UNKNOWN";
	char *tmp;

	i = 0;
	while (split[i])
	{
		if (split[i][0] == '&' && split[i][1] == '&' && !split[i][2])
		{
			split[i][0] = 'E';
			split[i][1] = 'T';
		}
		else if (split[i][0] == '|' && split[i][1] == '|' && !split[i][2])
		{
			split[i][0] = 'O';
			split[i][1] = 'U';
		}
		else if (!exists(split[i], envp))
		{
			tmp = split[i];
			split[i] = unk;
			free(tmp);
		}
		i++;
	}
	print_lexer(split);
}
