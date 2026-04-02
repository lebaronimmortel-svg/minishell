#include "../../header/header.h"

static int	has_n_flag(char *input)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (1)
	{
		while (input[i] && !(input[i] == '-' && input[i - 1] == ' '))
		{
			if (i && input[i] != ' ' && input[i] != '-' && input[i - 1] == ' ')
				break ;
			i++;
		}
		if (!input[i])
			break ;
		i++;
		while (input[i] && ft_isalpha((int)input[i]))
		{
			if (input[i] == 'n' && flag)
				flag = 2;
			if (input[i] != 'n')
				flag = 0;
			i++;
		}
	}
	if (flag == 2)
		return (1);
	else
		return (0);
}

static void	echo(char *input)
{
	int	i;

	i = 0;
	while (1)
	{
		while (input[i] && input[i] != ' ')
			i++;
		if (!input[i])
			return ;
		i++;
		if (!input[i])
			return ;
		if (input[i] != '-')
			break ;
	}
	printf("%s", &input[i]);
	if (has_n_flag(input))
		printf("\n");
}

int	status_code(char *input, t_data *data)
{
	int i;

	i = 0;
	while (input[i] && input[i] != ' ')
		i++;
	if (!input[i])
		return (data->error_code);
	return (ft_atoi(&input[i]));
}

void	exec_built_in(char *input, char **envp, t_data *data)
{
	if (!ft_strncmp(input, "pwd", 3) && ft_strlen(input) == 3)
		pwd();
	else if (!ft_strncmp(input, "unset ", 6))
		unset(&ft_split(input, ' ')[1], envp);
	else if (!ft_strncmp(input, "env", 3) && ft_strlen(input) == 3)
		env(envp);
	else if ((!ft_strncmp(input, "exit", 4) && ft_strlen(input) == 4) || (!ft_strncmp(input, "exit ", 5)))
		exit(status_code(input, data));
	else if ((!ft_strncmp(input, "echo ", 5)))
		echo(input);
}
